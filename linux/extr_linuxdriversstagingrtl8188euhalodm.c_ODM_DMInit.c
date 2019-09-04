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
struct odm_dm_struct {scalar_t__ AntDivType; } ;

/* Variables and functions */
 scalar_t__ CGCS_RX_HW_ANTDIV ; 
 scalar_t__ CG_TRX_HW_ANTDIV ; 
 scalar_t__ CG_TRX_SMART_ANTDIV ; 
 int /*<<< orphan*/  ODM_EdcaTurboInit (struct odm_dm_struct*) ; 
 int /*<<< orphan*/  ODM_RAInfo_Init_all (struct odm_dm_struct*) ; 
 int /*<<< orphan*/  odm_CmnInfoInit_Debug (struct odm_dm_struct*) ; 
 int /*<<< orphan*/  odm_CommonInfoSelfInit (struct odm_dm_struct*) ; 
 int /*<<< orphan*/  odm_DIGInit (struct odm_dm_struct*) ; 
 int /*<<< orphan*/  odm_DynamicTxPowerInit (struct odm_dm_struct*) ; 
 int /*<<< orphan*/  odm_InitHybridAntDiv (struct odm_dm_struct*) ; 
 int /*<<< orphan*/  odm_RateAdaptiveMaskInit (struct odm_dm_struct*) ; 
 int /*<<< orphan*/  odm_TXPowerTrackingInit (struct odm_dm_struct*) ; 

void ODM_DMInit(struct odm_dm_struct *pDM_Odm)
{
	/* 2012.05.03 Luke: For all IC series */
	odm_CommonInfoSelfInit(pDM_Odm);
	odm_CmnInfoInit_Debug(pDM_Odm);
	odm_DIGInit(pDM_Odm);
	odm_RateAdaptiveMaskInit(pDM_Odm);

	odm_DynamicTxPowerInit(pDM_Odm);
	odm_TXPowerTrackingInit(pDM_Odm);
	ODM_EdcaTurboInit(pDM_Odm);
	ODM_RAInfo_Init_all(pDM_Odm);
	if ((pDM_Odm->AntDivType == CG_TRX_HW_ANTDIV)	||
	    (pDM_Odm->AntDivType == CGCS_RX_HW_ANTDIV) ||
	    (pDM_Odm->AntDivType == CG_TRX_SMART_ANTDIV))
		odm_InitHybridAntDiv(pDM_Odm);
}