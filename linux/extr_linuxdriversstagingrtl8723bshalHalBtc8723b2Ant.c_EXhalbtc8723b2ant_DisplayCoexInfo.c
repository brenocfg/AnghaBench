#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_60__   TYPE_5__ ;
typedef  struct TYPE_59__   TYPE_51__ ;
typedef  struct TYPE_58__   TYPE_50__ ;
typedef  struct TYPE_57__   TYPE_4__ ;
typedef  struct TYPE_56__   TYPE_3__ ;
typedef  struct TYPE_55__   TYPE_2__ ;
typedef  struct TYPE_54__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int s32 ;
struct TYPE_60__ {scalar_t__ pgAntNum; int btdmAntNum; } ;
struct TYPE_59__ {scalar_t__ btStatus; int curPsTdma; scalar_t__ curBtDecPwrLvl; int bCurIgnoreWlanAct; int /*<<< orphan*/  btRf0x1eBackup; int /*<<< orphan*/  bAutoTdmaAdjust; int /*<<< orphan*/ * psTdmaPara; int /*<<< orphan*/  curDacSwingLvl; int /*<<< orphan*/  bCurDacSwingOn; int /*<<< orphan*/  bCurAdcBackOff; int /*<<< orphan*/  bCurAgcTableEn; int /*<<< orphan*/  bLimitedDig; int /*<<< orphan*/  bCurLowPenaltyRa; int /*<<< orphan*/  bCurRfRxLpfShrink; int /*<<< orphan*/ * wifiChnlInfo; } ;
struct TYPE_58__ {int btInfoExt; scalar_t__ highPriorityRx; int highPriorityTx; scalar_t__ lowPriorityRx; int lowPriorityTx; scalar_t__ bUnderLps; scalar_t__ bUnderIps; scalar_t__* btInfoC2hCnt; int /*<<< orphan*/ ** btInfoC2h; int /*<<< orphan*/  btRetryCnt; int /*<<< orphan*/  btRssi; scalar_t__ bC2hBtInquiryPage; } ;
struct TYPE_57__ {int /*<<< orphan*/  bA2dpExist; int /*<<< orphan*/  bPanExist; int /*<<< orphan*/  bHidExist; int /*<<< orphan*/  bScoExist; } ;
struct TYPE_54__ {scalar_t__ bBtDisabled; } ;
struct TYPE_55__ {int hciVersion; scalar_t__ bProfileNotified; } ;
struct TYPE_56__ {int* cliBuf; int (* fBtcRead1Byte ) (TYPE_3__*,int) ;scalar_t__ (* fBtcRead4Byte ) (TYPE_3__*,int) ;int /*<<< orphan*/  (* fBtcDispDbgMsg ) (TYPE_3__*,int /*<<< orphan*/ ) ;TYPE_1__ btInfo; int /*<<< orphan*/  (* fBtcGet ) (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__*) ;scalar_t__ bManualControl; TYPE_4__ btLinkInfo; TYPE_2__ stackInfo; TYPE_5__ boardInfo; } ;
typedef  TYPE_2__* PBTC_STACK_INFO ;
typedef  TYPE_3__* PBTC_COEXIST ;
typedef  TYPE_4__* PBTC_BT_LINK_INFO ;
typedef  TYPE_5__* PBTC_BOARD_INFO ;

/* Variables and functions */
 int BIT0 ; 
 int /*<<< orphan*/  BTC_DBG_DISP_BT_LINK_INFO ; 
 int /*<<< orphan*/  BTC_DBG_DISP_COEX_STATISTICS ; 
 int /*<<< orphan*/  BTC_DBG_DISP_FW_PWR_MODE_CMD ; 
 int /*<<< orphan*/  BTC_GET_BL_HS_OPERATION ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_LINK ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_ROAM ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_SCAN ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_UNDER_5G ; 
 int /*<<< orphan*/  BTC_GET_S4_HS_RSSI ; 
 int /*<<< orphan*/  BTC_GET_S4_WIFI_RSSI ; 
 int /*<<< orphan*/  BTC_GET_U1_AP_NUM ; 
 int /*<<< orphan*/  BTC_GET_U1_WIFI_DOT11_CHNL ; 
 int /*<<< orphan*/  BTC_GET_U1_WIFI_HS_CHNL ; 
 int /*<<< orphan*/  BTC_GET_U4_BT_PATCH_VER ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_BW ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_FW_VER ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_TRAFFIC_DIRECTION ; 
 scalar_t__ BTC_WIFI_BW_HT40 ; 
 scalar_t__ BTC_WIFI_BW_LEGACY ; 
 scalar_t__ BTC_WIFI_TRAFFIC_TX ; 
 scalar_t__ BT_8723B_2ANT_BT_STATUS_CONNECTED_IDLE ; 
 scalar_t__ BT_8723B_2ANT_BT_STATUS_NON_CONNECTED_IDLE ; 
 int BT_INFO_SRC_8723B_2ANT_MAX ; 
 int /*<<< orphan*/  BT_TMP_BUF_SIZE ; 
 int /*<<< orphan*/  CL_PRINTF (int*) ; 
 int /*<<< orphan*/  CL_SPRINTF (int*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * GLBtInfoSrc8723b2Ant ; 
 int /*<<< orphan*/  GLCoexVer8723b2Ant ; 
 int /*<<< orphan*/  GLCoexVerDate8723b2Ant ; 
 int /*<<< orphan*/  halbtc8723b2ant_MonitorBtCtr (TYPE_3__*) ; 
 TYPE_51__* pCoexDm ; 
 TYPE_50__* pCoexSta ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub10 (TYPE_3__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub11 (TYPE_3__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub12 (TYPE_3__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub13 (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub14 (TYPE_3__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub15 (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub16 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub17 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int stub18 (TYPE_3__*,int) ; 
 scalar_t__ stub19 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stub20 (TYPE_3__*,int) ; 
 int stub21 (TYPE_3__*,int) ; 
 int stub22 (TYPE_3__*,int) ; 
 scalar_t__ stub23 (TYPE_3__*,int) ; 
 scalar_t__ stub24 (TYPE_3__*,int) ; 
 scalar_t__ stub25 (TYPE_3__*,int) ; 
 int stub26 (TYPE_3__*,int) ; 
 int stub27 (TYPE_3__*,int) ; 
 scalar_t__ stub28 (TYPE_3__*,int) ; 
 int stub29 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub30 (TYPE_3__*,int) ; 
 int stub31 (TYPE_3__*,int) ; 
 scalar_t__ stub32 (TYPE_3__*,int) ; 
 int stub33 (TYPE_3__*,int) ; 
 scalar_t__ stub34 (TYPE_3__*,int) ; 
 scalar_t__ stub35 (TYPE_3__*,int) ; 
 scalar_t__ stub36 (TYPE_3__*,int) ; 
 scalar_t__ stub37 (TYPE_3__*,int) ; 
 int stub38 (TYPE_3__*,int) ; 
 int stub39 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub40 (TYPE_3__*,int) ; 
 scalar_t__ stub41 (TYPE_3__*,int) ; 
 scalar_t__ stub42 (TYPE_3__*,int) ; 
 int stub43 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stub44 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (TYPE_3__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub6 (TYPE_3__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub7 (TYPE_3__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub8 (TYPE_3__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub9 (TYPE_3__*,int /*<<< orphan*/ ,int*) ; 

void EXhalbtc8723b2ant_DisplayCoexInfo(PBTC_COEXIST pBtCoexist)
{
	PBTC_BOARD_INFO pBoardInfo = &pBtCoexist->boardInfo;
	PBTC_STACK_INFO pStackInfo = &pBtCoexist->stackInfo;
	PBTC_BT_LINK_INFO pBtLinkInfo = &pBtCoexist->btLinkInfo;
	u8 *cliBuf = pBtCoexist->cliBuf;
	u8 u1Tmp[4], i, btInfoExt, psTdmaCase = 0;
	u32 u4Tmp[4];
	bool bRoam = false, bScan = false, bLink = false, bWifiUnder5G = false;
	bool bBtHsOn = false, bWifiBusy = false;
	s32 wifiRssi = 0, btHsRssi = 0;
	u32 wifiBw, wifiTrafficDir, faOfdm, faCck;
	u8 wifiDot11Chnl, wifiHsChnl;
	u32 fwVer = 0, btPatchVer = 0;
	u8 apNum = 0;

	CL_SPRINTF(cliBuf, BT_TMP_BUF_SIZE, "\r\n ============[BT Coexist info]============");
	CL_PRINTF(cliBuf);

	if (pBtCoexist->bManualControl) {
		CL_SPRINTF(cliBuf, BT_TMP_BUF_SIZE, "\r\n ============[Under Manual Control]============");
		CL_PRINTF(cliBuf);
		CL_SPRINTF(cliBuf, BT_TMP_BUF_SIZE, "\r\n ==========================================");
		CL_PRINTF(cliBuf);
	}

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d/ %d ", "Ant PG number/ Ant mechanism:", \
		pBoardInfo->pgAntNum,
		pBoardInfo->btdmAntNum
	);
	CL_PRINTF(cliBuf);

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %s / %d", "BT stack/ hci ext ver", \
		(pStackInfo->bProfileNotified ? "Yes" : "No"),
		pStackInfo->hciVersion
	);
	CL_PRINTF(cliBuf);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_BT_PATCH_VER, &btPatchVer);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_FW_VER, &fwVer);
	CL_SPRINTF(cliBuf, BT_TMP_BUF_SIZE, "\r\n %-35s = %d_%x/ 0x%x/ 0x%x(%d)", "CoexVer/ FwVer/ PatchVer", \
		GLCoexVerDate8723b2Ant, GLCoexVer8723b2Ant, fwVer, btPatchVer, btPatchVer);
	CL_PRINTF(cliBuf);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_HS_OPERATION, &bBtHsOn);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U1_WIFI_DOT11_CHNL, &wifiDot11Chnl);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U1_WIFI_HS_CHNL, &wifiHsChnl);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d / %d(%d)", "Dot11 channel / HsChnl(HsMode)", \
		wifiDot11Chnl,
		wifiHsChnl,
		bBtHsOn
	);
	CL_PRINTF(cliBuf);

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %02x %02x %02x ", "H2C Wifi inform bt chnl Info", \
		pCoexDm->wifiChnlInfo[0],
		pCoexDm->wifiChnlInfo[1],
		pCoexDm->wifiChnlInfo[2]
	);
	CL_PRINTF(cliBuf);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_S4_WIFI_RSSI, &wifiRssi);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_S4_HS_RSSI, &btHsRssi);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U1_AP_NUM, &apNum);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d/ %d/ %d", "Wifi rssi/ HS rssi/ AP#", \
		wifiRssi,
		btHsRssi,
		apNum
	);
	CL_PRINTF(cliBuf);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_SCAN, &bScan);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_LINK, &bLink);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_ROAM, &bRoam);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d/ %d/ %d ", "Wifi bLink/ bRoam/ bScan", \
		bLink,
		bRoam,
		bScan
	);
	CL_PRINTF(cliBuf);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_UNDER_5G, &bWifiUnder5G);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_BW, &wifiBw);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_BUSY, &bWifiBusy);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_TRAFFIC_DIRECTION, &wifiTrafficDir);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %s / %s/ %s ", "Wifi status", \
		(bWifiUnder5G ? "5G" : "2.4G"),
		((BTC_WIFI_BW_LEGACY == wifiBw) ? "Legacy" : (((BTC_WIFI_BW_HT40 == wifiBw) ? "HT40" : "HT20"))),
		((!bWifiBusy) ? "idle" : ((BTC_WIFI_TRAFFIC_TX == wifiTrafficDir) ? "uplink" : "downlink"))
	);
	CL_PRINTF(cliBuf);

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = [%s/ %d/ %d] ", "BT [status/ rssi/ retryCnt]", \
		((pBtCoexist->btInfo.bBtDisabled) ? ("disabled") : ((pCoexSta->bC2hBtInquiryPage) ? ("inquiry/page scan") : ((BT_8723B_2ANT_BT_STATUS_NON_CONNECTED_IDLE == pCoexDm->btStatus) ? "non-connected idle" :
		((BT_8723B_2ANT_BT_STATUS_CONNECTED_IDLE == pCoexDm->btStatus) ? "connected-idle" : "busy")))),
		pCoexSta->btRssi,
		pCoexSta->btRetryCnt
	);
	CL_PRINTF(cliBuf);

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d / %d / %d / %d", "SCO/HID/PAN/A2DP", \
		pBtLinkInfo->bScoExist,
		pBtLinkInfo->bHidExist,
		pBtLinkInfo->bPanExist,
		pBtLinkInfo->bA2dpExist
	);
	CL_PRINTF(cliBuf);
	pBtCoexist->fBtcDispDbgMsg(pBtCoexist, BTC_DBG_DISP_BT_LINK_INFO);

	btInfoExt = pCoexSta->btInfoExt;
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %s", "BT Info A2DP rate", \
		(btInfoExt&BIT0) ? "Basic rate" : "EDR rate"
	);
	CL_PRINTF(cliBuf);

	for (i = 0; i < BT_INFO_SRC_8723B_2ANT_MAX; i++) {
		if (pCoexSta->btInfoC2hCnt[i]) {
			CL_SPRINTF(
				cliBuf,
				BT_TMP_BUF_SIZE,
				"\r\n %-35s = %02x %02x %02x %02x %02x %02x %02x(%d)", GLBtInfoSrc8723b2Ant[i], \
				pCoexSta->btInfoC2h[i][0],
				pCoexSta->btInfoC2h[i][1],
				pCoexSta->btInfoC2h[i][2],
				pCoexSta->btInfoC2h[i][3],
				pCoexSta->btInfoC2h[i][4],
				pCoexSta->btInfoC2h[i][5],
				pCoexSta->btInfoC2h[i][6],
				pCoexSta->btInfoC2hCnt[i]
			);
			CL_PRINTF(cliBuf);
		}
	}

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %s/%s", "PS state, IPS/LPS", \
		((pCoexSta->bUnderIps ? "IPS ON" : "IPS OFF")),
		((pCoexSta->bUnderLps ? "LPS ON" : "LPS OFF"))
	);
	CL_PRINTF(cliBuf);
	pBtCoexist->fBtcDispDbgMsg(pBtCoexist, BTC_DBG_DISP_FW_PWR_MODE_CMD);

	/*  Sw mechanism */
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s", "============[Sw mechanism]============"
	);
	CL_PRINTF(cliBuf);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d/ %d/ %d ", "SM1[ShRf/ LpRA/ LimDig]", \
		pCoexDm->bCurRfRxLpfShrink,
		pCoexDm->bCurLowPenaltyRa,
		pCoexDm->bLimitedDig
	);
	CL_PRINTF(cliBuf);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d/ %d/ %d(0x%x) ",
		"SM2[AgcT/ AdcB/ SwDacSwing(lvl)]", \
		pCoexDm->bCurAgcTableEn,
		pCoexDm->bCurAdcBackOff,
		pCoexDm->bCurDacSwingOn,
		pCoexDm->curDacSwingLvl
	);
	CL_PRINTF(cliBuf);

	/*  Fw mechanism */
	CL_SPRINTF(cliBuf, BT_TMP_BUF_SIZE, "\r\n %-35s", "============[Fw mechanism]============");
	CL_PRINTF(cliBuf);

	psTdmaCase = pCoexDm->curPsTdma;
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %02x %02x %02x %02x %02x case-%d (auto:%d)", "PS TDMA", \
		pCoexDm->psTdmaPara[0],
		pCoexDm->psTdmaPara[1],
		pCoexDm->psTdmaPara[2],
		pCoexDm->psTdmaPara[3],
		pCoexDm->psTdmaPara[4],
		psTdmaCase, pCoexDm->bAutoTdmaAdjust
	);
	CL_PRINTF(cliBuf);

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d/ %d ", "DecBtPwr/ IgnWlanAct", \
		pCoexDm->curBtDecPwrLvl,
		pCoexDm->bCurIgnoreWlanAct
	);
	CL_PRINTF(cliBuf);

	/*  Hw setting */
	CL_SPRINTF(cliBuf, BT_TMP_BUF_SIZE, "\r\n %-35s", "============[Hw setting]============");
	CL_PRINTF(cliBuf);

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = 0x%x", "RF-A, 0x1e initVal", \
		pCoexDm->btRf0x1eBackup
	);
	CL_PRINTF(cliBuf);

	u1Tmp[0] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x778);
	u4Tmp[0] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x880);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = 0x%x/ 0x%x", "0x778/0x880[29:25]", \
		u1Tmp[0],
		(u4Tmp[0]&0x3e000000) >> 25
	);
	CL_PRINTF(cliBuf);


	u4Tmp[0] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x948);
	u1Tmp[0] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x67);
	u1Tmp[1] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x765);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = 0x%x/ 0x%x/ 0x%x", "0x948/ 0x67[5] / 0x765", \
		u4Tmp[0],
		((u1Tmp[0]&0x20)>>5),
		u1Tmp[1]
	);
	CL_PRINTF(cliBuf);

	u4Tmp[0] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x92c);
	u4Tmp[1] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x930);
	u4Tmp[2] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x944);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = 0x%x/ 0x%x/ 0x%x", "0x92c[1:0]/ 0x930[7:0]/0x944[1:0]", \
		u4Tmp[0]&0x3,
		u4Tmp[1]&0xff,
		u4Tmp[2]&0x3
	);
	CL_PRINTF(cliBuf);


	u1Tmp[0] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x39);
	u1Tmp[1] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x40);
	u4Tmp[0] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x4c);
	u1Tmp[2] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x64);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = 0x%x/ 0x%x/ 0x%x/ 0x%x", "0x38[11]/0x40/0x4c[24:23]/0x64[0]", \
		((u1Tmp[0] & 0x8)>>3),
		u1Tmp[1],
		((u4Tmp[0]&0x01800000)>>23),
		u1Tmp[2]&0x1
	);
	CL_PRINTF(cliBuf);

	u4Tmp[0] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x550);
	u1Tmp[0] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x522);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = 0x%x/ 0x%x", "0x550(bcn ctrl)/0x522", \
		u4Tmp[0],
		u1Tmp[0]
	);
	CL_PRINTF(cliBuf);

	u4Tmp[0] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0xc50);
	u1Tmp[0] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x49c);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = 0x%x/ 0x%x", "0xc50(dig)/0x49c(null-drop)", \
		u4Tmp[0]&0xff,
		u1Tmp[0]
	);
	CL_PRINTF(cliBuf);

	u4Tmp[0] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0xda0);
	u4Tmp[1] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0xda4);
	u4Tmp[2] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0xda8);
	u4Tmp[3] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0xcf0);

	u1Tmp[0] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0xa5b);
	u1Tmp[1] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0xa5c);

	faOfdm =
		((u4Tmp[0]&0xffff0000) >> 16) +
		((u4Tmp[1]&0xffff0000) >> 16) +
		(u4Tmp[1] & 0xffff) +  (u4Tmp[2] & 0xffff) + \
		((u4Tmp[3]&0xffff0000) >> 16) +
		(u4Tmp[3] & 0xffff);

	faCck = (u1Tmp[0] << 8) + u1Tmp[1];

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = 0x%x/ 0x%x/ 0x%x", "OFDM-CCA/OFDM-FA/CCK-FA", \
		u4Tmp[0]&0xffff,
		faOfdm,
		faCck
	);
	CL_PRINTF(cliBuf);

	u4Tmp[0] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x6c0);
	u4Tmp[1] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x6c4);
	u4Tmp[2] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x6c8);
	u1Tmp[0] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x6cc);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = 0x%x/ 0x%x/ 0x%x/ 0x%x", "0x6c0/0x6c4/0x6c8/0x6cc(coexTable)", \
		u4Tmp[0],
		u4Tmp[1],
		u4Tmp[2],
		u1Tmp[0]
	);
	CL_PRINTF(cliBuf);

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d/ %d", "0x770(high-pri rx/tx)", \
		pCoexSta->highPriorityRx,
		pCoexSta->highPriorityTx
	);
	CL_PRINTF(cliBuf);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d/ %d", "0x774(low-pri rx/tx)", \
		pCoexSta->lowPriorityRx,
		pCoexSta->lowPriorityTx
	);
	CL_PRINTF(cliBuf);

	halbtc8723b2ant_MonitorBtCtr(pBtCoexist);
	pBtCoexist->fBtcDispDbgMsg(pBtCoexist, BTC_DBG_DISP_COEX_STATISTICS);
}