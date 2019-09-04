#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_13__ {scalar_t__ bAutoTdmaAdjust; } ;
struct TYPE_12__ {int /*<<< orphan*/  specialPktPeriodCnt; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* fBtcGet ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  ALGO_TRACE ; 
 int /*<<< orphan*/  BTC_GET_U4_BT_PATCH_VER ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_FW_VER ; 
 int /*<<< orphan*/  BTC_MSG_ALGORITHM ; 
 int /*<<< orphan*/  BTC_MSG_INTERFACE ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GLCoexVer8723b1Ant ; 
 int /*<<< orphan*/  GLCoexVerDate8723b1Ant ; 
 int /*<<< orphan*/  INTF_INIT ; 
 scalar_t__ halbtc8723b1ant_IsWifiStatusChanged (TYPE_1__*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_MonitorBtCtr (TYPE_1__*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_MonitorWiFiCtr (TYPE_1__*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_RunCoexistMechanism (TYPE_1__*) ; 
 TYPE_5__* pCoexDm ; 
 TYPE_4__* pCoexSta ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void EXhalbtc8723b1ant_Periodical(PBTC_COEXIST pBtCoexist)
{
	static u8 disVerInfoCnt;
	u32 fwVer = 0, btPatchVer = 0;

	BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], ==========================Periodical ===========================\n"));

	if (disVerInfoCnt <= 5) {
		disVerInfoCnt += 1;
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_INIT, ("[BTCoex], ****************************************************************\n"));
		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_BT_PATCH_VER, &btPatchVer);
		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_FW_VER, &fwVer);
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_INIT, ("[BTCoex], CoexVer/ FwVer/ PatchVer = %d_%x/ 0x%x/ 0x%x(%d)\n", \
			GLCoexVerDate8723b1Ant, GLCoexVer8723b1Ant, fwVer, btPatchVer, btPatchVer));
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_INIT, ("[BTCoex], ****************************************************************\n"));
	}

	halbtc8723b1ant_MonitorBtCtr(pBtCoexist);
	halbtc8723b1ant_MonitorWiFiCtr(pBtCoexist);

	if (
		halbtc8723b1ant_IsWifiStatusChanged(pBtCoexist) ||
		pCoexDm->bAutoTdmaAdjust
	)
		halbtc8723b1ant_RunCoexistMechanism(pBtCoexist);

	pCoexSta->specialPktPeriodCnt++;
}