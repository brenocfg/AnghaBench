#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int* mp_mode; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_CfoTrackingInit (TYPE_1__*) ; 
 int /*<<< orphan*/  ODM_ClearTxPowerTrackingState (TYPE_1__*) ; 
 int /*<<< orphan*/  ODM_EdcaTurboInit (TYPE_1__*) ; 
 int /*<<< orphan*/  odm_AdaptivityInit (TYPE_1__*) ; 
 int /*<<< orphan*/  odm_CmnInfoInit_Debug (TYPE_1__*) ; 
 int /*<<< orphan*/  odm_CommonInfoSelfInit (TYPE_1__*) ; 
 int /*<<< orphan*/  odm_DIGInit (TYPE_1__*) ; 
 int /*<<< orphan*/  odm_DynamicBBPowerSavingInit (TYPE_1__*) ; 
 int /*<<< orphan*/  odm_DynamicTxPowerInit (TYPE_1__*) ; 
 int /*<<< orphan*/  odm_NHMCounterStatisticsInit (TYPE_1__*) ; 
 int /*<<< orphan*/  odm_PathDiversityInit (TYPE_1__*) ; 
 int /*<<< orphan*/  odm_RSSIMonitorInit (TYPE_1__*) ; 
 int /*<<< orphan*/  odm_RateAdaptiveMaskInit (TYPE_1__*) ; 
 int /*<<< orphan*/  odm_SwAntDetectInit (TYPE_1__*) ; 
 int /*<<< orphan*/  odm_TXPowerTrackingInit (TYPE_1__*) ; 

void ODM_DMInit(PDM_ODM_T pDM_Odm)
{

	odm_CommonInfoSelfInit(pDM_Odm);
	odm_CmnInfoInit_Debug(pDM_Odm);
	odm_DIGInit(pDM_Odm);
	odm_NHMCounterStatisticsInit(pDM_Odm);
	odm_AdaptivityInit(pDM_Odm);
	odm_RateAdaptiveMaskInit(pDM_Odm);
	ODM_CfoTrackingInit(pDM_Odm);
	ODM_EdcaTurboInit(pDM_Odm);
	odm_RSSIMonitorInit(pDM_Odm);
	odm_TXPowerTrackingInit(pDM_Odm);

	ODM_ClearTxPowerTrackingState(pDM_Odm);

	if (*(pDM_Odm->mp_mode) != 1)
		odm_PathDiversityInit(pDM_Odm);

	odm_DynamicBBPowerSavingInit(pDM_Odm);
	odm_DynamicTxPowerInit(pDM_Odm);

	odm_SwAntDetectInit(pDM_Odm);
}