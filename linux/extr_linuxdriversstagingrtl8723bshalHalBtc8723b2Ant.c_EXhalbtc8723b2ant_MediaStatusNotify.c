#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_9__ {scalar_t__* wifiChnlInfo; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* fBtcFillH2c ) (TYPE_1__*,int,int,scalar_t__*) ;int /*<<< orphan*/  (* fBtcGet ) (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ;} ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  ALGO_TRACE_FW_EXEC ; 
 int /*<<< orphan*/  BTC_GET_U1_AP_NUM ; 
 int /*<<< orphan*/  BTC_GET_U1_WIFI_CENTRAL_CHNL ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_BW ; 
 scalar_t__ BTC_MEDIA_CONNECT ; 
 int /*<<< orphan*/  BTC_MSG_ALGORITHM ; 
 int /*<<< orphan*/  BTC_MSG_INTERFACE ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ BTC_WIFI_BW_HT40 ; 
 int /*<<< orphan*/  INTF_NOTIFY ; 
 TYPE_6__* pCoexDm ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int,int,scalar_t__*) ; 

void EXhalbtc8723b2ant_MediaStatusNotify(PBTC_COEXIST pBtCoexist, u8 type)
{
	u8 H2C_Parameter[3] = {0};
	u32 wifiBw;
	u8 wifiCentralChnl;
	u8 apNum = 0;

	if (BTC_MEDIA_CONNECT == type) {
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], MEDIA connect notify\n"));
	} else {
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], MEDIA disconnect notify\n"));
	}

	/*  only 2.4G we need to inform bt the chnl mask */
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U1_WIFI_CENTRAL_CHNL, &wifiCentralChnl);
	if ((BTC_MEDIA_CONNECT == type) && (wifiCentralChnl <= 14)) {
		H2C_Parameter[0] = 0x1;
		H2C_Parameter[1] = wifiCentralChnl;
		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_BW, &wifiBw);
		if (BTC_WIFI_BW_HT40 == wifiBw)
			H2C_Parameter[2] = 0x30;
		else {
			pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U1_AP_NUM, &apNum);
			if (apNum < 10)
				H2C_Parameter[2] = 0x30;
			else
				H2C_Parameter[2] = 0x20;
		}
	}

	pCoexDm->wifiChnlInfo[0] = H2C_Parameter[0];
	pCoexDm->wifiChnlInfo[1] = H2C_Parameter[1];
	pCoexDm->wifiChnlInfo[2] = H2C_Parameter[2];

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_FW_EXEC,
		(
			"[BTCoex], FW write 0x66 = 0x%x\n",
			H2C_Parameter[0]<<16|H2C_Parameter[1]<<8|H2C_Parameter[2]
		)
	);

	pBtCoexist->fBtcFillH2c(pBtCoexist, 0x66, 3, H2C_Parameter);
}