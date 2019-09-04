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
typedef  scalar_t__ u8 ;
struct hal_com_data {scalar_t__*** TxPwrByRateBase5G; scalar_t__*** TxPwrByRateBase2_4G; } ;
struct adapter {int dummy; } ;
typedef  enum RATE_SECTION { ____Placeholder_RATE_SECTION } RATE_SECTION ;

/* Variables and functions */
 scalar_t__ BAND_ON_2_4G ; 
 scalar_t__ BAND_ON_5G ; 
#define  CCK 137 
 int /*<<< orphan*/  DBG_871X (char*,scalar_t__,...) ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
#define  HT_MCS0_MCS7 136 
#define  HT_MCS16_MCS23 135 
#define  HT_MCS24_MCS31 134 
#define  HT_MCS8_MCS15 133 
 scalar_t__ ODM_RF_PATH_D ; 
#define  OFDM 132 
#define  VHT_1SSMCS0_1SSMCS9 131 
#define  VHT_2SSMCS0_2SSMCS9 130 
#define  VHT_3SSMCS0_3SSMCS9 129 
#define  VHT_4SSMCS0_4SSMCS9 128 

__attribute__((used)) static void
phy_SetTxPowerByRateBase(
	struct adapter *Adapter,
	u8 Band,
	u8 RfPath,
	enum RATE_SECTION	RateSection,
	u8 TxNum,
	u8 Value
)
{
	struct hal_com_data	*pHalData = GET_HAL_DATA(Adapter);

	if (RfPath > ODM_RF_PATH_D) {
		DBG_871X("Invalid Rf Path %d in phy_SetTxPowerByRatBase()\n", RfPath);
		return;
	}

	if (Band == BAND_ON_2_4G) {
		switch (RateSection) {
		case CCK:
			pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][0] = Value;
			break;
		case OFDM:
			pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][1] = Value;
			break;
		case HT_MCS0_MCS7:
			pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][2] = Value;
			break;
		case HT_MCS8_MCS15:
			pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][3] = Value;
			break;
		case HT_MCS16_MCS23:
			pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][4] = Value;
			break;
		case HT_MCS24_MCS31:
			pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][5] = Value;
			break;
		case VHT_1SSMCS0_1SSMCS9:
			pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][6] = Value;
			break;
		case VHT_2SSMCS0_2SSMCS9:
			pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][7] = Value;
			break;
		case VHT_3SSMCS0_3SSMCS9:
			pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][8] = Value;
			break;
		case VHT_4SSMCS0_4SSMCS9:
			pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][9] = Value;
			break;
		default:
			DBG_871X("Invalid RateSection %d in Band 2.4G, Rf Path %d, %dTx in phy_SetTxPowerByRateBase()\n",
					 RateSection, RfPath, TxNum);
			break;
		}
	} else if (Band == BAND_ON_5G) {
		switch (RateSection) {
		case OFDM:
			pHalData->TxPwrByRateBase5G[RfPath][TxNum][0] = Value;
			break;
		case HT_MCS0_MCS7:
			pHalData->TxPwrByRateBase5G[RfPath][TxNum][1] = Value;
			break;
		case HT_MCS8_MCS15:
			pHalData->TxPwrByRateBase5G[RfPath][TxNum][2] = Value;
			break;
		case HT_MCS16_MCS23:
			pHalData->TxPwrByRateBase5G[RfPath][TxNum][3] = Value;
			break;
		case HT_MCS24_MCS31:
			pHalData->TxPwrByRateBase5G[RfPath][TxNum][4] = Value;
			break;
		case VHT_1SSMCS0_1SSMCS9:
			pHalData->TxPwrByRateBase5G[RfPath][TxNum][5] = Value;
			break;
		case VHT_2SSMCS0_2SSMCS9:
			pHalData->TxPwrByRateBase5G[RfPath][TxNum][6] = Value;
			break;
		case VHT_3SSMCS0_3SSMCS9:
			pHalData->TxPwrByRateBase5G[RfPath][TxNum][7] = Value;
			break;
		case VHT_4SSMCS0_4SSMCS9:
			pHalData->TxPwrByRateBase5G[RfPath][TxNum][8] = Value;
			break;
		default:
			DBG_871X("Invalid RateSection %d in Band 5G, Rf Path %d, %dTx in phy_SetTxPowerByRateBase()\n",
					 RateSection, RfPath, TxNum);
			break;
		}
	} else
		DBG_871X("Invalid Band %d in phy_SetTxPowerByRateBase()\n", Band);
}