#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int CUTVersion; int ROMVer; int /*<<< orphan*/  VendorType; int /*<<< orphan*/  RFType; int /*<<< orphan*/  ChipType; int /*<<< orphan*/  ICType; } ;
struct hal_com_data {int /*<<< orphan*/  rf_type; TYPE_1__ VersionID; int /*<<< orphan*/  PolarityCtl; int /*<<< orphan*/  MultiFunc; int /*<<< orphan*/  RegulatorMode; } ;
struct adapter {int dummy; } ;
typedef  TYPE_1__ HAL_VERSION ;

/* Variables and functions */
 int BT_FUNC_EN ; 
 int /*<<< orphan*/  CHIP_8723B ; 
 int /*<<< orphan*/  CHIP_VENDOR_TSMC ; 
 int /*<<< orphan*/  CHIP_VENDOR_UMC ; 
 int CHIP_VER_RTL_MASK ; 
 int CHIP_VER_RTL_SHIFT ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int GPS_FUNC_EN ; 
 scalar_t__ IS_1T2R (TYPE_1__) ; 
 scalar_t__ IS_2T2R (TYPE_1__) ; 
 int /*<<< orphan*/  MSG_8192C (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NORMAL_CHIP ; 
 int /*<<< orphan*/  REG_GPIO_OUTSTS ; 
 int /*<<< orphan*/  REG_MULTI_FUNC_CTRL ; 
 int /*<<< orphan*/  REG_SYS_CFG ; 
 int /*<<< orphan*/  RF_1T1R ; 
 int /*<<< orphan*/  RF_1T2R ; 
 int /*<<< orphan*/  RF_2T2R ; 
 int RF_RL_ID ; 
 int /*<<< orphan*/  RF_TYPE_1T1R ; 
 int RTL_ID ; 
 int /*<<< orphan*/  RT_LDO_REGULATOR ; 
 int /*<<< orphan*/  RT_MULTI_FUNC_BT ; 
 int /*<<< orphan*/  RT_MULTI_FUNC_GPS ; 
 int /*<<< orphan*/  RT_MULTI_FUNC_NONE ; 
 int /*<<< orphan*/  RT_MULTI_FUNC_WIFI ; 
 int /*<<< orphan*/  RT_POLARITY_HIGH_ACT ; 
 int /*<<< orphan*/  RT_POLARITY_LOW_ACT ; 
 int /*<<< orphan*/  RT_SWITCHING_REGULATOR ; 
 int SPS_SEL ; 
 int /*<<< orphan*/  TEST_CHIP ; 
 int VENDOR_ID ; 
 int WL_FUNC_EN ; 
 int WL_HWPDN_SL ; 
 int /*<<< orphan*/  dump_chip_info (TYPE_1__) ; 
 int rtw_read32 (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HAL_VERSION ReadChipVersion8723B(struct adapter *padapter)
{
	u32 value32;
	HAL_VERSION ChipVersion;
	struct hal_com_data *pHalData;

/* YJ, TODO, move read chip type here */
	pHalData = GET_HAL_DATA(padapter);

	value32 = rtw_read32(padapter, REG_SYS_CFG);
	ChipVersion.ICType = CHIP_8723B;
	ChipVersion.ChipType = ((value32 & RTL_ID) ? TEST_CHIP : NORMAL_CHIP);
	ChipVersion.RFType = RF_TYPE_1T1R;
	ChipVersion.VendorType = ((value32 & VENDOR_ID) ? CHIP_VENDOR_UMC : CHIP_VENDOR_TSMC);
	ChipVersion.CUTVersion = (value32 & CHIP_VER_RTL_MASK)>>CHIP_VER_RTL_SHIFT; /*  IC version (CUT) */

	/*  For regulator mode. by tynli. 2011.01.14 */
	pHalData->RegulatorMode = ((value32 & SPS_SEL) ? RT_LDO_REGULATOR : RT_SWITCHING_REGULATOR);

	value32 = rtw_read32(padapter, REG_GPIO_OUTSTS);
	ChipVersion.ROMVer = ((value32 & RF_RL_ID) >> 20);	/*  ROM code version. */

	/*  For multi-function consideration. Added by Roger, 2010.10.06. */
	pHalData->MultiFunc = RT_MULTI_FUNC_NONE;
	value32 = rtw_read32(padapter, REG_MULTI_FUNC_CTRL);
	pHalData->MultiFunc |= ((value32 & WL_FUNC_EN) ? RT_MULTI_FUNC_WIFI : 0);
	pHalData->MultiFunc |= ((value32 & BT_FUNC_EN) ? RT_MULTI_FUNC_BT : 0);
	pHalData->MultiFunc |= ((value32 & GPS_FUNC_EN) ? RT_MULTI_FUNC_GPS : 0);
	pHalData->PolarityCtl = ((value32 & WL_HWPDN_SL) ? RT_POLARITY_HIGH_ACT : RT_POLARITY_LOW_ACT);
#if 1
	dump_chip_info(ChipVersion);
#endif
	pHalData->VersionID = ChipVersion;
	if (IS_1T2R(ChipVersion))
		pHalData->rf_type = RF_1T2R;
	else if (IS_2T2R(ChipVersion))
		pHalData->rf_type = RF_2T2R;
	else
		pHalData->rf_type = RF_1T1R;

	MSG_8192C("RF_Type is %x!!\n", pHalData->rf_type);

	return ChipVersion;
}