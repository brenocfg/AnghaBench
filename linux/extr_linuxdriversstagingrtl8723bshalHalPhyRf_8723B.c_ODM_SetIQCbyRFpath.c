#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int*** TxIQC_8723B; int*** RxIQC_8723B; } ;
struct TYPE_5__ {int /*<<< orphan*/  Adapter; TYPE_1__ RFCalibrateInfo; } ;
typedef  TYPE_1__* PODM_RF_CAL_T ;
typedef  TYPE_2__* PDM_ODM_T ;

/* Variables and functions */
 size_t IDX_0xC14 ; 
 size_t IDX_0xC4C ; 
 size_t IDX_0xC80 ; 
 size_t IDX_0xC94 ; 
 size_t IDX_0xCA0 ; 
 size_t KEY ; 
 size_t PATH_S0 ; 
 size_t PATH_S1 ; 
 int /*<<< orphan*/  PHY_SetBBReg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 size_t VAL ; 
 int /*<<< orphan*/  bMaskDWord ; 

void ODM_SetIQCbyRFpath(PDM_ODM_T pDM_Odm, u32 RFpath)
{

	PODM_RF_CAL_T pRFCalibrateInfo = &(pDM_Odm->RFCalibrateInfo);

	if (
		(pRFCalibrateInfo->TxIQC_8723B[PATH_S0][IDX_0xC80][VAL] != 0x0) &&
		(pRFCalibrateInfo->RxIQC_8723B[PATH_S0][IDX_0xC14][VAL] != 0x0) &&
		(pRFCalibrateInfo->TxIQC_8723B[PATH_S1][IDX_0xC80][VAL] != 0x0) &&
		(pRFCalibrateInfo->RxIQC_8723B[PATH_S1][IDX_0xC14][VAL] != 0x0)
	) {
		if (RFpath) { /* S1: RFpath = 0, S0:RFpath = 1 */
			/* S0 TX IQC */
			PHY_SetBBReg(pDM_Odm->Adapter, pRFCalibrateInfo->TxIQC_8723B[PATH_S0][IDX_0xC94][KEY], bMaskDWord, pRFCalibrateInfo->TxIQC_8723B[PATH_S0][IDX_0xC94][VAL]);
			PHY_SetBBReg(pDM_Odm->Adapter, pRFCalibrateInfo->TxIQC_8723B[PATH_S0][IDX_0xC80][KEY], bMaskDWord, pRFCalibrateInfo->TxIQC_8723B[PATH_S0][IDX_0xC80][VAL]);
			PHY_SetBBReg(pDM_Odm->Adapter, pRFCalibrateInfo->TxIQC_8723B[PATH_S0][IDX_0xC4C][KEY], bMaskDWord, pRFCalibrateInfo->TxIQC_8723B[PATH_S0][IDX_0xC4C][VAL]);
			/* S0 RX IQC */
			PHY_SetBBReg(pDM_Odm->Adapter, pRFCalibrateInfo->RxIQC_8723B[PATH_S0][IDX_0xC14][KEY], bMaskDWord, pRFCalibrateInfo->RxIQC_8723B[PATH_S0][IDX_0xC14][VAL]);
			PHY_SetBBReg(pDM_Odm->Adapter, pRFCalibrateInfo->RxIQC_8723B[PATH_S0][IDX_0xCA0][KEY], bMaskDWord, pRFCalibrateInfo->RxIQC_8723B[PATH_S0][IDX_0xCA0][VAL]);
		} else {
			/* S1 TX IQC */
			PHY_SetBBReg(pDM_Odm->Adapter, pRFCalibrateInfo->TxIQC_8723B[PATH_S1][IDX_0xC94][KEY], bMaskDWord, pRFCalibrateInfo->TxIQC_8723B[PATH_S1][IDX_0xC94][VAL]);
			PHY_SetBBReg(pDM_Odm->Adapter, pRFCalibrateInfo->TxIQC_8723B[PATH_S1][IDX_0xC80][KEY], bMaskDWord, pRFCalibrateInfo->TxIQC_8723B[PATH_S1][IDX_0xC80][VAL]);
			PHY_SetBBReg(pDM_Odm->Adapter, pRFCalibrateInfo->TxIQC_8723B[PATH_S1][IDX_0xC4C][KEY], bMaskDWord, pRFCalibrateInfo->TxIQC_8723B[PATH_S1][IDX_0xC4C][VAL]);
			/* S1 RX IQC */
			PHY_SetBBReg(pDM_Odm->Adapter, pRFCalibrateInfo->RxIQC_8723B[PATH_S1][IDX_0xC14][KEY], bMaskDWord, pRFCalibrateInfo->RxIQC_8723B[PATH_S1][IDX_0xC14][VAL]);
			PHY_SetBBReg(pDM_Odm->Adapter, pRFCalibrateInfo->RxIQC_8723B[PATH_S1][IDX_0xCA0][KEY], bMaskDWord, pRFCalibrateInfo->RxIQC_8723B[PATH_S1][IDX_0xCA0][VAL]);
		}
	}
}