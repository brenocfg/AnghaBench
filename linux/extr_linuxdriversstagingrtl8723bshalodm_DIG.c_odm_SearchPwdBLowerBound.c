#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int s8 ;
struct TYPE_4__ {int TH_L2H_ini; int TH_EDCCA_HL_diff; int txEdcca1; int TxHangFlg; int H2L_lb; int L2H_lb; int Adaptivity_IGI_upper; scalar_t__ txEdcca0; int /*<<< orphan*/  Adapter; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 int BIT29 ; 
 int BIT30 ; 
 int /*<<< orphan*/  ODM_COMP_DIG ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_REG_RPT_11N ; 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ODM_Write_DIG (TYPE_1__*,int) ; 
 int PHY_QueryBBReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_SetBBReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bMaskByte0 ; 
 int /*<<< orphan*/  bMaskByte2 ; 
 int /*<<< orphan*/  bMaskDWord ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  rOFDM0_ECCAThreshold ; 

void odm_SearchPwdBLowerBound(void *pDM_VOID, u8 IGI_target)
{
	PDM_ODM_T pDM_Odm = (PDM_ODM_T)pDM_VOID;
	u32 value32 = 0;
	u8 cnt, IGI;
	bool bAdjust = true;
	s8 TH_L2H_dmc, TH_H2L_dmc;
	s8 Diff;

	IGI = 0x50; /*  find H2L, L2H lower bound */
	ODM_Write_DIG(pDM_Odm, IGI);


	Diff = IGI_target-(s8)IGI;
	TH_L2H_dmc = pDM_Odm->TH_L2H_ini + Diff;
	if (TH_L2H_dmc > 10)
		TH_L2H_dmc = 10;
	TH_H2L_dmc = TH_L2H_dmc - pDM_Odm->TH_EDCCA_HL_diff;
	PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_ECCAThreshold, bMaskByte0, (u8)TH_L2H_dmc);
	PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_ECCAThreshold, bMaskByte2, (u8)TH_H2L_dmc);

	mdelay(5);

	while (bAdjust) {
		for (cnt = 0; cnt < 20; cnt++) {
			value32 = PHY_QueryBBReg(pDM_Odm->Adapter, ODM_REG_RPT_11N, bMaskDWord);

			if (value32 & BIT30)
				pDM_Odm->txEdcca1 = pDM_Odm->txEdcca1 + 1;
			else if (value32 & BIT29)
				pDM_Odm->txEdcca1 = pDM_Odm->txEdcca1 + 1;
			else
				pDM_Odm->txEdcca0 = pDM_Odm->txEdcca0 + 1;
		}
		/* DbgPrint("txEdcca1 = %d, txEdcca0 = %d\n", pDM_Odm->txEdcca1, pDM_Odm->txEdcca0); */

		if (pDM_Odm->txEdcca1 > 5) {
			IGI = IGI-1;
			TH_L2H_dmc = TH_L2H_dmc + 1;
			if (TH_L2H_dmc > 10)
				TH_L2H_dmc = 10;
			TH_H2L_dmc = TH_L2H_dmc - pDM_Odm->TH_EDCCA_HL_diff;
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_ECCAThreshold, bMaskByte0, (u8)TH_L2H_dmc);
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_ECCAThreshold, bMaskByte2, (u8)TH_H2L_dmc);

			pDM_Odm->TxHangFlg = true;
			pDM_Odm->txEdcca1 = 0;
			pDM_Odm->txEdcca0 = 0;

			if (TH_L2H_dmc == 10) {
				bAdjust = false;
				pDM_Odm->TxHangFlg = false;
				pDM_Odm->txEdcca1 = 0;
				pDM_Odm->txEdcca0 = 0;
				pDM_Odm->H2L_lb = TH_H2L_dmc;
				pDM_Odm->L2H_lb = TH_L2H_dmc;
				pDM_Odm->Adaptivity_IGI_upper = IGI;
			}
		} else {
			bAdjust = false;
			pDM_Odm->TxHangFlg = false;
			pDM_Odm->txEdcca1 = 0;
			pDM_Odm->txEdcca0 = 0;
			pDM_Odm->H2L_lb = TH_H2L_dmc;
			pDM_Odm->L2H_lb = TH_L2H_dmc;
			pDM_Odm->Adaptivity_IGI_upper = IGI;
		}
	}

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("IGI = 0x%x, H2L_lb = 0x%x, L2H_lb = 0x%x\n", IGI, pDM_Odm->H2L_lb, pDM_Odm->L2H_lb));
}