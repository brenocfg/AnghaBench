#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  Adapter; } ;
struct hal_com_data {TYPE_1__ odmpriv; } ;
struct adapter {int dummy; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 int BIT28 ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  IQK_DELAY_TIME_8723B ; 
 int /*<<< orphan*/  ODM_COMP_CALIBRATION ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RF_PATH_A ; 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int PHY_QueryBBReg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_SetBBReg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PHY_SetRFReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  RF_RCK_OS ; 
 int /*<<< orphan*/  RF_TXPA_G1 ; 
 int /*<<< orphan*/  RF_TXPA_G2 ; 
 int /*<<< orphan*/  RF_WE_LUT ; 
 int /*<<< orphan*/  bMaskDWord ; 
 int /*<<< orphan*/  bMaskH3Bytes ; 
 int bRFRegOffsetMask ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 int rFPGA0_IQK ; 
 int rIQK_AGC_Pts ; 
 int rIQK_AGC_Rsp ; 
 int rRx_IQK ; 
 int rRx_IQK_PI_A ; 
 int rRx_IQK_PI_B ; 
 int rRx_IQK_Tone_A ; 
 int rRx_IQK_Tone_B ; 
 int rRx_Power_After_IQK_A_2 ; 
 int rTx_IQK ; 
 int rTx_IQK_PI_A ; 
 int rTx_IQK_PI_B ; 
 int rTx_IQK_Tone_A ; 
 int rTx_IQK_Tone_B ; 
 int rTx_Power_After_IQK_A ; 
 int rTx_Power_Before_IQK_A ; 

__attribute__((used)) static u8 phy_PathA_IQK_8723B(
	struct adapter *padapter, bool configPathB, u8 RF_Path
)
{
	u32 regEAC, regE94, regE9C, tmp, Path_SEL_BB /*, regEA4*/;
	u8 result = 0x00;

	struct hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	PDM_ODM_T		pDM_Odm = &pHalData->odmpriv;

	/*  Save RF Path */
	Path_SEL_BB = PHY_QueryBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord);

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path A IQK!\n"));

	/* leave IQK mode */
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x000000);

	/* 	enable path A PA in TXIQK mode */
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_WE_LUT, 0x80000, 0x1);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_RCK_OS, bRFRegOffsetMask, 0x18000);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_TXPA_G1, bRFRegOffsetMask, 0x0003f);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_TXPA_G2, bRFRegOffsetMask, 0xc7f87);
	/* 	disable path B PA in TXIQK mode */
/* 	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0xed, bRFRegOffsetMask, 0x00020); */
/* 	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0x43, bRFRegOffsetMask, 0x40ec1); */

	/* 1 Tx IQK */
	/* IQK setting */
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK, bMaskDWord, 0x01007c00);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK, bMaskDWord, 0x01004800);
	/* path-A IQK setting */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path-A IQK setting!\n")); */
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_Tone_A, bMaskDWord, 0x18008c1c);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_Tone_A, bMaskDWord, 0x38008c1c);
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_Tone_B, bMaskDWord, 0x38008c1c);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_Tone_B, bMaskDWord, 0x38008c1c);
/* 	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_PI_A, bMaskDWord, 0x8214010a); */
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_PI_A, bMaskDWord, 0x821303ea);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_PI_A, bMaskDWord, 0x28110000);
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_PI_B, bMaskDWord, 0x82110000);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_PI_B, bMaskDWord, 0x28110000);

	/* LO calibration setting */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("LO calibration setting!\n")); */
	PHY_SetBBReg(pDM_Odm->Adapter, rIQK_AGC_Rsp, bMaskDWord, 0x00462911);

	/* enter IQK mode */
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x808000);

	/* Ant switch */
	if (configPathB || (RF_Path == 0))
		/*  wifi switch to S1 */
		PHY_SetBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord, 0x00000000);
	else
		/*  wifi switch to S0 */
		PHY_SetBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord, 0x00000280);

	/* GNT_BT = 0 */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x764, bMaskDWord, 0x00000800);

	/* One shot, path A LOK & IQK */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("One shot, path A LOK & IQK!\n")); */
	PHY_SetBBReg(pDM_Odm->Adapter, rIQK_AGC_Pts, bMaskDWord, 0xf9000000);
	PHY_SetBBReg(pDM_Odm->Adapter, rIQK_AGC_Pts, bMaskDWord, 0xf8000000);

	/*  delay x ms */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Delay %d ms for One shot, path A LOK & IQK.\n", IQK_DELAY_TIME_8723B)); */
	/* PlatformStallExecution(IQK_DELAY_TIME_8723B*1000); */
	mdelay(IQK_DELAY_TIME_8723B);

	/* restore Ant Path */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord, Path_SEL_BB);
	/* GNT_BT = 1 */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x764, bMaskDWord, 0x00001800);

	/* leave IQK mode */
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x000000);


	/*  Check failed */
	regEAC = PHY_QueryBBReg(pDM_Odm->Adapter, rRx_Power_After_IQK_A_2, bMaskDWord);
	regE94 = PHY_QueryBBReg(pDM_Odm->Adapter, rTx_Power_Before_IQK_A, bMaskDWord);
	regE9C = PHY_QueryBBReg(pDM_Odm->Adapter, rTx_Power_After_IQK_A, bMaskDWord);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("0xeac = 0x%x\n", regEAC));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("0xe94 = 0x%x, 0xe9c = 0x%x\n", regE94, regE9C));
	/* monitor image power before & after IQK */
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("0xe90(before IQK) = 0x%x, 0xe98(afer IQK) = 0x%x\n",
	PHY_QueryBBReg(pDM_Odm->Adapter, 0xe90, bMaskDWord), PHY_QueryBBReg(pDM_Odm->Adapter, 0xe98, bMaskDWord)));


	/* Allen 20131125 */
	tmp = (regE9C & 0x03FF0000)>>16;
	if ((tmp & 0x200) > 0)
		tmp = 0x400 - tmp;

	if (
		!(regEAC & BIT28) &&
		(((regE94 & 0x03FF0000)>>16) != 0x142) &&
		(((regE9C & 0x03FF0000)>>16) != 0x42) &&
		(((regE94 & 0x03FF0000)>>16) < 0x110) &&
		(((regE94 & 0x03FF0000)>>16) > 0xf0) &&
		(tmp < 0xf)
	)
		result |= 0x01;
	else					/* if Tx not OK, ignore Rx */
		return result;

	return result;
}