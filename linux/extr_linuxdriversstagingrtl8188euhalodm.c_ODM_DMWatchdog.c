#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct odm_dm_struct {scalar_t__ AntDivType; scalar_t__* pbPowerSaving; } ;

/* Variables and functions */
 scalar_t__ CGCS_RX_HW_ANTDIV ; 
 scalar_t__ CG_TRX_HW_ANTDIV ; 
 scalar_t__ CG_TRX_SMART_ANTDIV ; 
 int /*<<< orphan*/  ODM_TXPowerTrackingCheck (struct odm_dm_struct*) ; 
 int /*<<< orphan*/  odm_CCKPacketDetectionThresh (struct odm_dm_struct*) ; 
 int /*<<< orphan*/  odm_CmnInfoHook_Debug (struct odm_dm_struct*) ; 
 int /*<<< orphan*/  odm_CmnInfoUpdate_Debug (struct odm_dm_struct*) ; 
 int /*<<< orphan*/  odm_CommonInfoSelfUpdate (struct odm_dm_struct*) ; 
 int /*<<< orphan*/  odm_DIG (struct odm_dm_struct*) ; 
 int /*<<< orphan*/  odm_EdcaTurboCheck (struct odm_dm_struct*) ; 
 int /*<<< orphan*/  odm_FalseAlarmCounterStatistics (struct odm_dm_struct*) ; 
 int /*<<< orphan*/  odm_HwAntDiv (struct odm_dm_struct*) ; 
 int /*<<< orphan*/  odm_RSSIMonitorCheck (struct odm_dm_struct*) ; 
 int /*<<< orphan*/  odm_RefreshRateAdaptiveMask (struct odm_dm_struct*) ; 

void ODM_DMWatchdog(struct odm_dm_struct *pDM_Odm)
{
	/* 2012.05.03 Luke: For all IC series */
	odm_CmnInfoHook_Debug(pDM_Odm);
	odm_CmnInfoUpdate_Debug(pDM_Odm);
	odm_CommonInfoSelfUpdate(pDM_Odm);
	odm_FalseAlarmCounterStatistics(pDM_Odm);
	odm_RSSIMonitorCheck(pDM_Odm);

	/* Fix Leave LPS issue */
	odm_DIG(pDM_Odm);
	odm_CCKPacketDetectionThresh(pDM_Odm);

	if (*(pDM_Odm->pbPowerSaving))
		return;

	odm_RefreshRateAdaptiveMask(pDM_Odm);

	if ((pDM_Odm->AntDivType ==  CG_TRX_HW_ANTDIV)	||
	    (pDM_Odm->AntDivType == CGCS_RX_HW_ANTDIV)	||
	    (pDM_Odm->AntDivType == CG_TRX_SMART_ANTDIV))
		odm_HwAntDiv(pDM_Odm);

	ODM_TXPowerTrackingCheck(pDM_Odm);
	odm_EdcaTurboCheck(pDM_Odm);
}