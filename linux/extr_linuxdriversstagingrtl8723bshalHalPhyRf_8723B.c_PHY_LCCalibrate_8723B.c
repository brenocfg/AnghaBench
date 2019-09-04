#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_6__ {int bLCKInProgress; } ;
struct TYPE_7__ {int SupportAbility; int /*<<< orphan*/  InterfaceIndex; TYPE_1__ RFCalibrateInfo; scalar_t__* pbScanInProcess; } ;
typedef  TYPE_2__* PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_CALIBRATION ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int ODM_RF_CALIBRATION ; 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  phy_LCCalibrate_8723B (TYPE_2__*,int) ; 

void PHY_LCCalibrate_8723B(PDM_ODM_T pDM_Odm)
{
	bool		bSingleTone = false, bCarrierSuppression = false;
	u32 		timeout = 2000, timecount = 0;
	u32 		StartTime;
	s32			ProgressingTime;

#if DISABLE_BB_RF
	return;
#endif

	if (!(pDM_Odm->SupportAbility & ODM_RF_CALIBRATION))
		return;

	/*  20120213<Kordan> Turn on when continuous Tx to pass lab testing. (required by Edlu) */
	if (bSingleTone || bCarrierSuppression)
		return;

	StartTime = jiffies;
	while (*(pDM_Odm->pbScanInProcess) && timecount < timeout) {
		mdelay(50);
		timecount += 50;
	}

	pDM_Odm->RFCalibrateInfo.bLCKInProgress = true;


	phy_LCCalibrate_8723B(pDM_Odm, false);


	pDM_Odm->RFCalibrateInfo.bLCKInProgress = false;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("LCK:Finish!!!interface %d\n", pDM_Odm->InterfaceIndex));
	ProgressingTime = jiffies_to_msecs(jiffies - StartTime);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("LCK ProgressingTime = %d\n", ProgressingTime));
}