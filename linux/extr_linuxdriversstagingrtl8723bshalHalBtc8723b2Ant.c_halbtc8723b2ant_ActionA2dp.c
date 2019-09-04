#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_17__ {int /*<<< orphan*/  (* fBtcGet ) (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ;int /*<<< orphan*/  (* fBtcSetRfReg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ;} ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_U1_AP_NUM ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_BW ; 
 int /*<<< orphan*/  BTC_RF_A ; 
 scalar_t__ BTC_RSSI_HIGH (int) ; 
 int BTC_RSSI_STATE_HIGH ; 
 int BTC_RSSI_STATE_STAY_HIGH ; 
 scalar_t__ BTC_WIFI_BW_HT40 ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int halbtc8723b2ant_BtRssiState (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8723b2ant_CoexTableWithType (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_DecBtPwr (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_FwDacSwingLvl (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_LimitedRx (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_PsTdma (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_SwMechanism1 (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_SwMechanism2 (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_TdmaDurationAdjust (TYPE_1__*,int,int,int) ; 
 int halbtc8723b2ant_WifiRssiState (TYPE_1__*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void halbtc8723b2ant_ActionA2dp(PBTC_COEXIST pBtCoexist)
{
	u8 wifiRssiState, wifiRssiState1, btRssiState;
	u32 wifiBw;
	u8 apNum = 0;

	wifiRssiState = halbtc8723b2ant_WifiRssiState(pBtCoexist, 0, 2, 15, 0);
	wifiRssiState1 = halbtc8723b2ant_WifiRssiState(pBtCoexist, 1, 2, 40, 0);
	btRssiState = halbtc8723b2ant_BtRssiState(2, 29, 0);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U1_AP_NUM, &apNum);

	/*  define the office environment */
	if (apNum >= 10 && BTC_RSSI_HIGH(wifiRssiState1)) {
		/* DbgPrint(" AP#>10(%d)\n", apNum); */
		pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);
		halbtc8723b2ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, false, 0x8);
		halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 6);
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);
		halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 0);
		halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 1);

		/*  sw mechanism */
		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_BW, &wifiBw);
		if (BTC_WIFI_BW_HT40 == wifiBw) {
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, true, 0x18);
		} else {
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, true, 0x18);
		}
		return;
	}

	pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);
	halbtc8723b2ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, false, 0x8);

	halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 6);

	if (BTC_RSSI_HIGH(btRssiState))
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 2);
	else
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);

	halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 7);

	if (
		(btRssiState == BTC_RSSI_STATE_HIGH) ||
		(btRssiState == BTC_RSSI_STATE_STAY_HIGH)
	)
		halbtc8723b2ant_TdmaDurationAdjust(pBtCoexist, false, false, 1);
	else
		halbtc8723b2ant_TdmaDurationAdjust(pBtCoexist, false, true, 1);

	/*  sw mechanism */
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_BW, &wifiBw);
	if (BTC_WIFI_BW_HT40 == wifiBw) {
		if (
			(wifiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wifiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) {
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, false, 0x18);
		} else {
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
		}
	} else {
		if (
			(wifiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wifiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) {
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, false, 0x18);
		} else {
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
		}
	}
}