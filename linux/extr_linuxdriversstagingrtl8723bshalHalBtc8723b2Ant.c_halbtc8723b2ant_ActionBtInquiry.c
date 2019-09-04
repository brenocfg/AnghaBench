#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int bNeedRecover0x948; int /*<<< orphan*/  backup0x948; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* fBtcRead4Byte ) (TYPE_1__*,int) ;int /*<<< orphan*/  (* fBtcGet ) (TYPE_1__*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* fBtcSet ) (TYPE_1__*,int /*<<< orphan*/ ,int*) ;} ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_WIFI_AT_AUX ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 int /*<<< orphan*/  BTC_SET_ACT_DISABLE_LOW_POWER ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  halbtc8723b2ant_CoexTableWithType (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_DecBtPwr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8723b2ant_FwDacSwingLvl (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_PsTdma (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_SetAntPath (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_SwMechanism1 (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_SwMechanism2 (TYPE_1__*,int,int,int,int) ; 
 TYPE_5__* pCoexDm ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int) ; 

__attribute__((used)) static void halbtc8723b2ant_ActionBtInquiry(PBTC_COEXIST pBtCoexist)
{
	bool bWifiConnected = false;
	bool bLowPwrDisable = true;

	pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_ACT_DISABLE_LOW_POWER, &bLowPwrDisable);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_CONNECTED, &bWifiConnected);

	if (bWifiConnected) {
		halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 7);
		halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 3);
	} else {
		halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 0);
		halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 1);
	}

	halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, FORCE_EXEC, 6);
	halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);

	halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
	halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);

	pCoexDm->bNeedRecover0x948 = true;
	pCoexDm->backup0x948 = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x948);

	halbtc8723b2ant_SetAntPath(pBtCoexist, BTC_ANT_WIFI_AT_AUX, false, false);
}