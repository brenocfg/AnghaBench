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
typedef  int /*<<< orphan*/  vht3ssRates ;
typedef  int /*<<< orphan*/  vht2ssRates ;
typedef  int /*<<< orphan*/  vht1ssRates ;
typedef  scalar_t__ u8 ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  ofdmRates ;
typedef  int /*<<< orphan*/  mcs8_15Rates ;
typedef  int /*<<< orphan*/  mcs16_23Rates ;
typedef  int /*<<< orphan*/  mcs0_7Rates ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ BAND_ON_2_4G ; 
 scalar_t__ BAND_ON_5G ; 
 scalar_t__ MGN_11M ; 
 scalar_t__ MGN_12M ; 
 scalar_t__ MGN_18M ; 
 scalar_t__ MGN_1M ; 
 scalar_t__ MGN_24M ; 
 scalar_t__ MGN_2M ; 
 scalar_t__ MGN_36M ; 
 scalar_t__ MGN_48M ; 
 scalar_t__ MGN_54M ; 
 scalar_t__ MGN_5_5M ; 
 scalar_t__ MGN_6M ; 
 scalar_t__ MGN_9M ; 
 scalar_t__ MGN_MCS0 ; 
 scalar_t__ MGN_MCS1 ; 
 scalar_t__ MGN_MCS10 ; 
 scalar_t__ MGN_MCS11 ; 
 scalar_t__ MGN_MCS12 ; 
 scalar_t__ MGN_MCS13 ; 
 scalar_t__ MGN_MCS14 ; 
 scalar_t__ MGN_MCS15 ; 
 scalar_t__ MGN_MCS16 ; 
 scalar_t__ MGN_MCS17 ; 
 scalar_t__ MGN_MCS18 ; 
 scalar_t__ MGN_MCS19 ; 
 scalar_t__ MGN_MCS2 ; 
 scalar_t__ MGN_MCS20 ; 
 scalar_t__ MGN_MCS21 ; 
 scalar_t__ MGN_MCS22 ; 
 scalar_t__ MGN_MCS23 ; 
 scalar_t__ MGN_MCS3 ; 
 scalar_t__ MGN_MCS4 ; 
 scalar_t__ MGN_MCS5 ; 
 scalar_t__ MGN_MCS6 ; 
 scalar_t__ MGN_MCS7 ; 
 scalar_t__ MGN_MCS8 ; 
 scalar_t__ MGN_MCS9 ; 
 scalar_t__ MGN_VHT1SS_MCS0 ; 
 scalar_t__ MGN_VHT1SS_MCS1 ; 
 scalar_t__ MGN_VHT1SS_MCS2 ; 
 scalar_t__ MGN_VHT1SS_MCS3 ; 
 scalar_t__ MGN_VHT1SS_MCS4 ; 
 scalar_t__ MGN_VHT1SS_MCS5 ; 
 scalar_t__ MGN_VHT1SS_MCS6 ; 
 scalar_t__ MGN_VHT1SS_MCS7 ; 
 scalar_t__ MGN_VHT1SS_MCS8 ; 
 scalar_t__ MGN_VHT1SS_MCS9 ; 
 scalar_t__ MGN_VHT2SS_MCS0 ; 
 scalar_t__ MGN_VHT2SS_MCS1 ; 
 scalar_t__ MGN_VHT2SS_MCS2 ; 
 scalar_t__ MGN_VHT2SS_MCS3 ; 
 scalar_t__ MGN_VHT2SS_MCS4 ; 
 scalar_t__ MGN_VHT2SS_MCS5 ; 
 scalar_t__ MGN_VHT2SS_MCS6 ; 
 scalar_t__ MGN_VHT2SS_MCS7 ; 
 scalar_t__ MGN_VHT2SS_MCS8 ; 
 scalar_t__ MGN_VHT2SS_MCS9 ; 
 scalar_t__ MGN_VHT3SS_MCS0 ; 
 scalar_t__ MGN_VHT3SS_MCS1 ; 
 scalar_t__ MGN_VHT3SS_MCS2 ; 
 scalar_t__ MGN_VHT3SS_MCS3 ; 
 scalar_t__ MGN_VHT3SS_MCS4 ; 
 scalar_t__ MGN_VHT3SS_MCS5 ; 
 scalar_t__ MGN_VHT3SS_MCS6 ; 
 scalar_t__ MGN_VHT3SS_MCS7 ; 
 scalar_t__ MGN_VHT3SS_MCS8 ; 
 scalar_t__ MGN_VHT3SS_MCS9 ; 
 scalar_t__ ODM_RF_PATH_A ; 
 scalar_t__ ODM_RF_PATH_D ; 
 scalar_t__ PHY_GetTxPowerByRate (struct adapter*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PHY_SetTxPowerByRate (struct adapter*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ RF_1TX ; 
 scalar_t__ RF_MAX_TX_NUM ; 

__attribute__((used)) static void
phy_ConvertTxPowerByRateInDbmToRelativeValues(
struct adapter *padapter
	)
{
	u8	base = 0, i = 0, value = 0, band = 0, path = 0, txNum = 0;
	u8	cckRates[4] = {
		MGN_1M, MGN_2M, MGN_5_5M, MGN_11M
	};
	u8	ofdmRates[8] = {
		MGN_6M, MGN_9M, MGN_12M, MGN_18M, MGN_24M, MGN_36M, MGN_48M, MGN_54M
	};
	u8 mcs0_7Rates[8] = {
		MGN_MCS0, MGN_MCS1, MGN_MCS2, MGN_MCS3, MGN_MCS4, MGN_MCS5, MGN_MCS6, MGN_MCS7
	};
	u8 mcs8_15Rates[8] = {
		MGN_MCS8, MGN_MCS9, MGN_MCS10, MGN_MCS11, MGN_MCS12, MGN_MCS13, MGN_MCS14, MGN_MCS15
	};
	u8 mcs16_23Rates[8] = {
		MGN_MCS16, MGN_MCS17, MGN_MCS18, MGN_MCS19, MGN_MCS20, MGN_MCS21, MGN_MCS22, MGN_MCS23
	};
	u8 vht1ssRates[10] = {
		MGN_VHT1SS_MCS0, MGN_VHT1SS_MCS1, MGN_VHT1SS_MCS2, MGN_VHT1SS_MCS3, MGN_VHT1SS_MCS4,
		MGN_VHT1SS_MCS5, MGN_VHT1SS_MCS6, MGN_VHT1SS_MCS7, MGN_VHT1SS_MCS8, MGN_VHT1SS_MCS9
	};
	u8 vht2ssRates[10] = {
		MGN_VHT2SS_MCS0, MGN_VHT2SS_MCS1, MGN_VHT2SS_MCS2, MGN_VHT2SS_MCS3, MGN_VHT2SS_MCS4,
		MGN_VHT2SS_MCS5, MGN_VHT2SS_MCS6, MGN_VHT2SS_MCS7, MGN_VHT2SS_MCS8, MGN_VHT2SS_MCS9
	};
	u8 vht3ssRates[10] = {
		MGN_VHT3SS_MCS0, MGN_VHT3SS_MCS1, MGN_VHT3SS_MCS2, MGN_VHT3SS_MCS3, MGN_VHT3SS_MCS4,
		MGN_VHT3SS_MCS5, MGN_VHT3SS_MCS6, MGN_VHT3SS_MCS7, MGN_VHT3SS_MCS8, MGN_VHT3SS_MCS9
	};

	/* DBG_871X("===>PHY_ConvertTxPowerByRateInDbmToRelativeValues()\n"); */

	for (band = BAND_ON_2_4G; band <= BAND_ON_5G; ++band) {
		for (path = ODM_RF_PATH_A; path <= ODM_RF_PATH_D; ++path) {
			for (txNum = RF_1TX; txNum < RF_MAX_TX_NUM; ++txNum) {
				/*  CCK */
				base = PHY_GetTxPowerByRate(padapter, band, path, txNum, MGN_11M);
				for (i = 0; i < ARRAY_SIZE(cckRates); ++i) {
					value = PHY_GetTxPowerByRate(padapter, band, path, txNum, cckRates[i]);
					PHY_SetTxPowerByRate(padapter, band, path, txNum, cckRates[i], value - base);
				}

				/*  OFDM */
				base = PHY_GetTxPowerByRate(padapter, band, path, txNum, MGN_54M);
				for (i = 0; i < sizeof(ofdmRates); ++i) {
					value = PHY_GetTxPowerByRate(padapter, band, path, txNum, ofdmRates[i]);
					PHY_SetTxPowerByRate(padapter, band, path, txNum, ofdmRates[i], value - base);
				}

				/*  HT MCS0~7 */
				base = PHY_GetTxPowerByRate(padapter, band, path, txNum, MGN_MCS7);
				for (i = 0; i < sizeof(mcs0_7Rates); ++i) {
					value = PHY_GetTxPowerByRate(padapter, band, path, txNum, mcs0_7Rates[i]);
					PHY_SetTxPowerByRate(padapter, band, path, txNum, mcs0_7Rates[i], value - base);
				}

				/*  HT MCS8~15 */
				base = PHY_GetTxPowerByRate(padapter, band, path, txNum, MGN_MCS15);
				for (i = 0; i < sizeof(mcs8_15Rates); ++i) {
					value = PHY_GetTxPowerByRate(padapter, band, path, txNum, mcs8_15Rates[i]);
					PHY_SetTxPowerByRate(padapter, band, path, txNum, mcs8_15Rates[i], value - base);
				}

				/*  HT MCS16~23 */
				base = PHY_GetTxPowerByRate(padapter, band, path, txNum, MGN_MCS23);
				for (i = 0; i < sizeof(mcs16_23Rates); ++i) {
					value = PHY_GetTxPowerByRate(padapter, band, path, txNum, mcs16_23Rates[i]);
					PHY_SetTxPowerByRate(padapter, band, path, txNum, mcs16_23Rates[i], value - base);
				}

				/*  VHT 1SS */
				base = PHY_GetTxPowerByRate(padapter, band, path, txNum, MGN_VHT1SS_MCS7);
				for (i = 0; i < sizeof(vht1ssRates); ++i) {
					value = PHY_GetTxPowerByRate(padapter, band, path, txNum, vht1ssRates[i]);
					PHY_SetTxPowerByRate(padapter, band, path, txNum, vht1ssRates[i], value - base);
				}

				/*  VHT 2SS */
				base = PHY_GetTxPowerByRate(padapter, band, path, txNum, MGN_VHT2SS_MCS7);
				for (i = 0; i < sizeof(vht2ssRates); ++i) {
					value = PHY_GetTxPowerByRate(padapter, band, path, txNum, vht2ssRates[i]);
					PHY_SetTxPowerByRate(padapter, band, path, txNum, vht2ssRates[i], value - base);
				}

				/*  VHT 3SS */
				base = PHY_GetTxPowerByRate(padapter, band, path, txNum, MGN_VHT3SS_MCS7);
				for (i = 0; i < sizeof(vht3ssRates); ++i) {
					value = PHY_GetTxPowerByRate(padapter, band, path, txNum, vht3ssRates[i]);
					PHY_SetTxPowerByRate(padapter, band, path, txNum, vht3ssRates[i], value - base);
				}
			}
		}
	}

	/* DBG_871X("<===PHY_ConvertTxPowerByRateInDbmToRelativeValues()\n"); */
}