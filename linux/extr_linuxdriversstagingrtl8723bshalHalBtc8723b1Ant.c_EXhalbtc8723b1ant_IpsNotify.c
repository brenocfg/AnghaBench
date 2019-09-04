#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_11__ {int bUnderIps; } ;
struct TYPE_10__ {scalar_t__ bStopCoexDm; scalar_t__ bManualControl; } ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_BT ; 
 scalar_t__ BTC_IPS_ENTER ; 
 scalar_t__ BTC_IPS_LEAVE ; 
 int /*<<< orphan*/  BTC_MSG_INTERFACE ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  INTF_NOTIFY ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  halbtc8723b1ant_CoexTableWithType (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8723b1ant_InitCoexDm (TYPE_1__*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_InitHwConfig (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_PsTdma (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8723b1ant_QueryBtInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_SetAntPath (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* pCoexSta ; 

void EXhalbtc8723b1ant_IpsNotify(PBTC_COEXIST pBtCoexist, u8 type)
{
	if (pBtCoexist->bManualControl ||	pBtCoexist->bStopCoexDm)
		return;

	if (BTC_IPS_ENTER == type) {
		BTC_PRINT(
			BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], IPS ENTER notify\n")
		);
		pCoexSta->bUnderIps = true;

		halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 0);
		halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 0);
		halbtc8723b1ant_SetAntPath(pBtCoexist, BTC_ANT_PATH_BT, false, true);
	} else if (BTC_IPS_LEAVE == type) {
		BTC_PRINT(
			BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], IPS LEAVE notify\n")
		);
		pCoexSta->bUnderIps = false;

		halbtc8723b1ant_InitHwConfig(pBtCoexist, false, false);
		halbtc8723b1ant_InitCoexDm(pBtCoexist);
		halbtc8723b1ant_QueryBtInfo(pBtCoexist);
	}
}