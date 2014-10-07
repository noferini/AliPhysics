#ifndef ALIEMCALTRIGGERMAKER_H
#define ALIEMCALTRIGGERMAKER_H

// $Id: AliEmcalTriggerMaker.h 64593 2013-10-18 10:23:58Z loizides $

class TClonesArray;
class AliEmcalTriggerSetupInfo;
class AliAODCaloTrigger;
class AliVVZERO;

#include "AliEMCALTriggerTypes.h"
#include "AliAnalysisTaskEmcal.h"

class AliEmcalTriggerMaker : public AliAnalysisTaskEmcal {
 public:
  enum TriggerMakerTriggerType_t {
    kTMEMCalJet = 0,
    kTMEMCalGamma = 1,
    kTMEMCalLevel0 = 2
  };
  AliEmcalTriggerMaker();
  AliEmcalTriggerMaker(const char *name);
  virtual ~AliEmcalTriggerMaker();

  void SetCaloTriggersOutName(const char *name)     { fCaloTriggersOutName      = name; }
  void SetCaloTriggerSetupOutName(const char *name) { fCaloTriggerSetupOutName  = name; }
  void SetTriggerThresholdJetLow   ( Int_t a, Int_t b, Int_t c ) { fThresholdConstants[2][0] = a; fThresholdConstants[2][1] = b; fThresholdConstants[2][2] = c; }
  void SetTriggerThresholdJetHigh  ( Int_t a, Int_t b, Int_t c ) { fThresholdConstants[0][0] = a; fThresholdConstants[0][1] = b; fThresholdConstants[0][2] = c; }
  void SetTriggerThresholdGammaLow ( Int_t a, Int_t b, Int_t c ) { fThresholdConstants[3][0] = a; fThresholdConstants[3][1] = b; fThresholdConstants[3][2] = c; }
  void SetTriggerThresholdGammaHigh( Int_t a, Int_t b, Int_t c ) { fThresholdConstants[3][0] = a; fThresholdConstants[1][1] = b; fThresholdConstants[1][2] = c; }
  void SetV0InName(const char *name) { fV0InName      = name; }

  Bool_t IsEJE(Int_t tBits) const { if( tBits & ( 1 << (kTriggerTypeEnd + kL1JetLow) | 1 << (kTriggerTypeEnd + kL1JetHigh) | 1 << (kL1JetLow) | 1 << (kL1JetHigh) )) return kTRUE; else return kFALSE; }
  Bool_t IsEGA(Int_t tBits) const { if( tBits & ( 1 << (kTriggerTypeEnd + kL1GammaLow) | 1 << (kTriggerTypeEnd + kL1GammaHigh) | 1 << (kL1GammaLow) | 1 << (kL1GammaHigh) )) return kTRUE; else return kFALSE; }
  Bool_t IsLevel0(Int_t tBits) const { if( tBits & (1 << (kTriggerTypeEnd + kL0) | (1 << kL0))) return kTRUE; return kFALSE; }

 protected:  
  void                       ExecOnce();
  Bool_t                     Run();
  void                       RunSimpleOfflineTrigger();
  Bool_t                     NextTrigger( Bool_t &isOfflineSimple );
  AliEmcalTriggerPatchInfo*  ProcessPatch(TriggerMakerTriggerType_t type, Bool_t isOfflineSimple);

  TString                    fCaloTriggersOutName;      // name of output track array
  TString                    fCaloTriggerSetupOutName;  // name of output track array
  TString                    fV0InName;                 // name of output track array
  Int_t                      fThresholdConstants[4][3]; // simple offline trigger thresholds constants
  TClonesArray              *fCaloTriggersOut;          //!trigger array out
  AliEmcalTriggerSetupInfo  *fCaloTriggerSetupOut;      //!trigger setup
  AliAODCaloTrigger         *fSimpleOfflineTriggers;    //!simple offline trigger
  AliVVZERO                 *fV0;                       //!V0 object
  Double_t                   fPatchADCSimple[48][64];   //!patch map for simple offline trigger
  Int_t                      fPatchADC[48][64];         //!ADC values map
  Int_t                      fITrigger;                 //!trigger counter

 private:
  AliEmcalTriggerMaker(const AliEmcalTriggerMaker&);            // not implemented
  AliEmcalTriggerMaker &operator=(const AliEmcalTriggerMaker&); // not implemented

  ClassDef(AliEmcalTriggerMaker, 4) // Task to make array of EMCAL trigger patches
};
#endif
