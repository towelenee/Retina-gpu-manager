// $Id: $
#ifndef PATPIXELHITMANAGER_H 
#define PATPIXELHITMANAGER_H 1

#include "PixelEvent.h"
#include "PatPixelHit.h"

#include "GaudiAlg/GaudiTool.h"
#include "GaudiKernel/IIncidentSvc.h"
#include "GaudiKernel/IIncidentListener.h"

#include "VPDet/DeVP.h"
#include "Event/VPLiteCluster.h"

#include "PatPixelSensor.h"

#include <vector>
#include <map>

using namespace std;

static const InterfaceID IID_PatPixelHitManager ( "PatPixelHitManager", 1, 0 );

/** @class PatPixelHitManager PatPixelHitManager.h
 *  Tool to handle the Pixel velo geometry and hits, from FastVelo
 *
 *  @author Olivier Callot
 *  @date   2012-01-05
 */
class PatPixelHitManager : public GaudiTool, public IIncidentListener {
public: 

  // dcampora
  PixelEvent event;
  std::map<int, PatPixelHit*> patPixelHitsIndex;

  // Return the interface ID
  static const InterfaceID& interfaceID() { return IID_PatPixelHitManager; }

  /// Standard constructor
  PatPixelHitManager( const std::string& type, 
                      const std::string& name,
                      const IInterface* parent);

  virtual ~PatPixelHitManager( ); ///< Destructor

  virtual StatusCode initialize();

  virtual StatusCode finalize();

  void buildHits();

  void clearHits();

  void handle ( const Incident& incident );

  PatPixelHits& hits( unsigned int sensor ) { return m_sensors[sensor]->hits(); }

  PatPixelSensor* sensor( unsigned int n ) { return m_sensors[n]; }

  unsigned int firstSensor()   const { return m_firstSensor;   }
  unsigned int lastSensor()    const { return m_lastSensor;    }

  int nbHits()  const { return m_nextInPool - m_pool.begin(); }
  int maxSize() const { return m_maxSize; }

  StatusCode rebuildGeometry();  ///< Recompute the geometry in case of change

  void sortByX();

protected:

private:
  DeVP* m_veloPix;

  std::vector<PatPixelHit>  m_pool;
  std::vector<PatPixelHit>::iterator m_nextInPool;
  std::vector<PatPixelSensor*> m_sensors;
  unsigned int m_firstSensor;
  unsigned int m_lastSensor;
  int m_maxSize;
  bool m_eventReady;
};
#endif // PATPIXELHITMANAGER_H
