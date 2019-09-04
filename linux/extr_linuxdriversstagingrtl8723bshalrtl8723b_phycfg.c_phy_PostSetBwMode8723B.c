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
typedef  int /*<<< orphan*/  u8 ;
struct hal_com_data {int CurrentChannelBW; int nCur40MhzPrimeSC; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int BIT26 ; 
 int BIT27 ; 
 int BIT30 ; 
 int BIT31 ; 
#define  CHANNEL_WIDTH_20 129 
#define  CHANNEL_WIDTH_40 128 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int HAL_PRIME_CHNL_OFFSET_LOWER ; 
 int /*<<< orphan*/  PHY_RF6052SetBandwidth8723B (struct adapter*,int) ; 
 int /*<<< orphan*/  PHY_SetBBReg (struct adapter*,int,int,int) ; 
 int /*<<< orphan*/  REG_DATA_SC_8723B ; 
 int bCCKSideBand ; 
 int bRFMOD ; 
 int /*<<< orphan*/  phy_GetSecondaryChnl_8723B (struct adapter*) ; 
 int /*<<< orphan*/  phy_SetRegBW_8723B (struct adapter*,int) ; 
 int rCCK0_System ; 
 int rFPGA0_RFMOD ; 
 int rFPGA1_RFMOD ; 
 int rOFDM0_TxPseudoNoiseWgt ; 
 int rOFDM1_LSTF ; 
 int /*<<< orphan*/  rtw_write8 (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void phy_PostSetBwMode8723B(struct adapter *Adapter)
{
	u8 SubChnlNum = 0;
	struct hal_com_data *pHalData = GET_HAL_DATA(Adapter);


	/* 3 Set Reg668 Reg440 BW */
	phy_SetRegBW_8723B(Adapter, pHalData->CurrentChannelBW);

	/* 3 Set Reg483 */
	SubChnlNum = phy_GetSecondaryChnl_8723B(Adapter);
	rtw_write8(Adapter, REG_DATA_SC_8723B, SubChnlNum);

	/* 3 */
	/* 3<2>Set PHY related register */
	/* 3 */
	switch (pHalData->CurrentChannelBW) {
	/* 20 MHz channel*/
	case CHANNEL_WIDTH_20:
		PHY_SetBBReg(Adapter, rFPGA0_RFMOD, bRFMOD, 0x0);

		PHY_SetBBReg(Adapter, rFPGA1_RFMOD, bRFMOD, 0x0);

/* 			PHY_SetBBReg(Adapter, rFPGA0_AnalogParameter2, BIT10, 1); */

		PHY_SetBBReg(Adapter, rOFDM0_TxPseudoNoiseWgt, (BIT31|BIT30), 0x0);
		break;

	/* 40 MHz channel*/
	case CHANNEL_WIDTH_40:
		PHY_SetBBReg(Adapter, rFPGA0_RFMOD, bRFMOD, 0x1);

		PHY_SetBBReg(Adapter, rFPGA1_RFMOD, bRFMOD, 0x1);

		/*  Set Control channel to upper or lower. These settings are required only for 40MHz */
		PHY_SetBBReg(Adapter, rCCK0_System, bCCKSideBand, (pHalData->nCur40MhzPrimeSC>>1));

		PHY_SetBBReg(Adapter, rOFDM1_LSTF, 0xC00, pHalData->nCur40MhzPrimeSC);

/* PHY_SetBBReg(Adapter, rFPGA0_AnalogParameter2, BIT10, 0); */

		PHY_SetBBReg(Adapter, 0x818, (BIT26|BIT27), (pHalData->nCur40MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_LOWER) ? 2 : 1);

		break;

	default:
		/*RT_TRACE(COMP_DBG, DBG_LOUD, ("phy_SetBWMode8723B(): unknown Bandwidth: %#X\n"\
					, pHalData->CurrentChannelBW));*/
		break;
	}

	/* 3<3>Set RF related register */
	PHY_RF6052SetBandwidth8723B(Adapter, pHalData->CurrentChannelBW);
}