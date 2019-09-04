#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_27__ {scalar_t__ bScoExist; scalar_t__ bBtLinkExist; scalar_t__ bA2dpExist; } ;
struct TYPE_26__ {int /*<<< orphan*/  (* fBtcGet ) (TYPE_1__*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* fBtcSet ) (TYPE_1__*,int /*<<< orphan*/ ,int*) ;scalar_t__ bStopCoexDm; scalar_t__ bManualControl; TYPE_2__ btLinkInfo; } ;
struct TYPE_25__ {scalar_t__ btStatus; } ;
struct TYPE_24__ {scalar_t__ bC2hBtInquiryPage; scalar_t__ bUnderIps; } ;
typedef  TYPE_1__* PBTC_COEXIST ;
typedef  TYPE_2__* PBTC_BT_LINK_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ALGO_TRACE ; 
 int /*<<< orphan*/  BTC_GET_BL_HS_OPERATION ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_LINK ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_ROAM ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_SCAN ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_LINK_STATUS ; 
 int /*<<< orphan*/  BTC_MSG_ALGORITHM ; 
 int /*<<< orphan*/  BTC_MSG_INTERFACE ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BTC_SET_BL_INC_SCAN_DEV_NUM ; 
 scalar_t__ BT_8723B_1ANT_BT_STATUS_ACL_BUSY ; 
 scalar_t__ BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY ; 
 scalar_t__ BT_8723B_1ANT_BT_STATUS_SCO_BUSY ; 
 int /*<<< orphan*/  INTF_NOTIFY ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int WIFI_P2P_GO_CONNECTED ; 
 int /*<<< orphan*/  halbtc8723b1ant_ActionBtInquiry (TYPE_1__*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_ActionHs (TYPE_1__*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_ActionWifiConnected (TYPE_1__*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_ActionWifiMultiPort (TYPE_1__*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_ActionWifiNotConnected (TYPE_1__*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_ActionWifiNotConnectedAssoAuth (TYPE_1__*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_ActionWifiNotConnectedScan (TYPE_1__*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_LimitedRx (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_LimitedTx (TYPE_1__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_RunSwCoexistMechanism (TYPE_1__*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_SwMechanism (TYPE_1__*,int) ; 
 TYPE_11__* pCoexDm ; 
 TYPE_10__* pCoexSta ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub7 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void halbtc8723b1ant_RunCoexistMechanism(PBTC_COEXIST pBtCoexist)
{
	PBTC_BT_LINK_INFO pBtLinkInfo = &pBtCoexist->btLinkInfo;
	bool bWifiConnected = false, bBtHsOn = false;
	bool bIncreaseScanDevNum = false;
	bool bBtCtrlAggBufSize = false;
	u8 aggBufSize = 5;
	u32 wifiLinkStatus = 0;
	u32 numOfWifiLink = 0;

	BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], RunCoexistMechanism() ===>\n"));

	if (pBtCoexist->bManualControl) {
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], RunCoexistMechanism(), return for Manual CTRL <===\n"));
		return;
	}

	if (pBtCoexist->bStopCoexDm) {
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], RunCoexistMechanism(), return for Stop Coex DM <===\n"));
		return;
	}

	if (pCoexSta->bUnderIps) {
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], wifi is under IPS !!!\n"));
		return;
	}

	if (
		(BT_8723B_1ANT_BT_STATUS_ACL_BUSY == pCoexDm->btStatus) ||
		(BT_8723B_1ANT_BT_STATUS_SCO_BUSY == pCoexDm->btStatus) ||
		(BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY == pCoexDm->btStatus)
	){
		bIncreaseScanDevNum = true;
	}

	pBtCoexist->fBtcSet(
		pBtCoexist,
		BTC_SET_BL_INC_SCAN_DEV_NUM,
		&bIncreaseScanDevNum
	);
	pBtCoexist->fBtcGet(
		pBtCoexist,
		BTC_GET_BL_WIFI_CONNECTED,
		&bWifiConnected
	);

	pBtCoexist->fBtcGet(
		pBtCoexist,
		BTC_GET_U4_WIFI_LINK_STATUS,
		&wifiLinkStatus
	);
	numOfWifiLink = wifiLinkStatus>>16;

	if ((numOfWifiLink >= 2) || (wifiLinkStatus&WIFI_P2P_GO_CONNECTED)) {
		BTC_PRINT(
			BTC_MSG_INTERFACE,
			INTF_NOTIFY,
			(
				"############# [BTCoex],  Multi-Port numOfWifiLink = %d, wifiLinkStatus = 0x%x\n",
				numOfWifiLink,
				wifiLinkStatus
			)
		);
		halbtc8723b1ant_LimitedTx(pBtCoexist, NORMAL_EXEC, 0, 0, 0, 0);
		halbtc8723b1ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, bBtCtrlAggBufSize, aggBufSize);

		if ((pBtLinkInfo->bA2dpExist) && (pCoexSta->bC2hBtInquiryPage)) {
			BTC_PRINT(
				BTC_MSG_INTERFACE,
				INTF_NOTIFY,
				("############# [BTCoex],  BT Is Inquirying\n")
			);
			halbtc8723b1ant_ActionBtInquiry(pBtCoexist);
		} else
			halbtc8723b1ant_ActionWifiMultiPort(pBtCoexist);

		return;
	}

	if ((pBtLinkInfo->bBtLinkExist) && (bWifiConnected)) {
		halbtc8723b1ant_LimitedTx(pBtCoexist, NORMAL_EXEC, 1, 1, 0, 1);

		if (pBtLinkInfo->bScoExist)
			halbtc8723b1ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, true, 0x5);
		else
			halbtc8723b1ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, true, 0x8);

		halbtc8723b1ant_SwMechanism(pBtCoexist, true);
		halbtc8723b1ant_RunSwCoexistMechanism(pBtCoexist);  /* just print debug message */
	} else {
		halbtc8723b1ant_LimitedTx(pBtCoexist, NORMAL_EXEC, 0, 0, 0, 0);

		halbtc8723b1ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, false, 0x5);

		halbtc8723b1ant_SwMechanism(pBtCoexist, false);
		halbtc8723b1ant_RunSwCoexistMechanism(pBtCoexist); /* just print debug message */
	}

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_HS_OPERATION, &bBtHsOn);
	if (pCoexSta->bC2hBtInquiryPage) {
		BTC_PRINT(
			BTC_MSG_INTERFACE,
			INTF_NOTIFY,
			("############# [BTCoex],  BT Is Inquirying\n")
		);
		halbtc8723b1ant_ActionBtInquiry(pBtCoexist);
		return;
	} else if (bBtHsOn) {
		halbtc8723b1ant_ActionHs(pBtCoexist);
		return;
	}


	if (!bWifiConnected) {
		bool bScan = false, bLink = false, bRoam = false;

		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], wifi is non connected-idle !!!\n"));

		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_SCAN, &bScan);
		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_LINK, &bLink);
		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_ROAM, &bRoam);

		if (bScan || bLink || bRoam) {
			 if (bScan)
				halbtc8723b1ant_ActionWifiNotConnectedScan(pBtCoexist);
			 else
				halbtc8723b1ant_ActionWifiNotConnectedAssoAuth(pBtCoexist);
		} else
			halbtc8723b1ant_ActionWifiNotConnected(pBtCoexist);
	} else /*  wifi LPS/Busy */
		halbtc8723b1ant_ActionWifiConnected(pBtCoexist);
}