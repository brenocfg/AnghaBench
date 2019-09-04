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
struct odm_dm_struct {int /*<<< orphan*/ * pbPowerSaving; int /*<<< orphan*/ * pbScanInProcess; int /*<<< orphan*/ * pChannel; int /*<<< orphan*/ * pBandWidth; int /*<<< orphan*/ * pSecurity; int /*<<< orphan*/ * pSecChOffset; int /*<<< orphan*/ * pWirelessMode; int /*<<< orphan*/ * pNumRxBytesUnicast; int /*<<< orphan*/ * pNumTxBytesUnicast; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_COMMON ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct odm_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void odm_CmnInfoHook_Debug(struct odm_dm_struct *pDM_Odm)
{
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("odm_CmnInfoHook_Debug==>\n"));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("pNumTxBytesUnicast=%llu\n", *(pDM_Odm->pNumTxBytesUnicast)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("pNumRxBytesUnicast=%llu\n", *(pDM_Odm->pNumRxBytesUnicast)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("pWirelessMode=0x%x\n", *(pDM_Odm->pWirelessMode)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("pSecChOffset=%d\n", *(pDM_Odm->pSecChOffset)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("pSecurity=%d\n", *(pDM_Odm->pSecurity)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("pBandWidth=%d\n", *(pDM_Odm->pBandWidth)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("pChannel=%d\n", *(pDM_Odm->pChannel)));

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("pbScanInProcess=%d\n", *(pDM_Odm->pbScanInProcess)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("pbPowerSaving=%d\n", *(pDM_Odm->pbPowerSaving)));
}