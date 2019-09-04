#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_11__ {int /*<<< orphan*/  (* fBtcWrite1ByteBitMask ) (TYPE_1__*,int,int,int) ;int /*<<< orphan*/  (* fBtcGet ) (TYPE_1__*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* fBtcWrite1Byte ) (TYPE_1__*,int,int) ;int /*<<< orphan*/  (* fBtcFillH2c ) (TYPE_1__*,int,int,int*) ;int /*<<< orphan*/  (* fBtcSetRfReg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ;} ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_WIFI_IS_IN_MP_MODE ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_FW_VER ; 
 int /*<<< orphan*/  BTC_RF_A ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int,int,int*) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub7 (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  stub8 (TYPE_1__*,int,int,int) ; 

__attribute__((used)) static void halbtc8723b2ant_WifiOffHwCfg(PBTC_COEXIST pBtCoexist)
{
	bool bIsInMpMode = false;
	u8 H2C_Parameter[2] = {0};
	u32 fwVer = 0;

	/*  set wlan_act to low */
	pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x76e, 0x4);

	pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x780); /* WiFi goto standby while GNT_BT 0-->1 */
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_FW_VER, &fwVer);
	if (fwVer >= 0x180000) {
		/* Use H2C to set GNT_BT to HIGH */
		H2C_Parameter[0] = 1;
		pBtCoexist->fBtcFillH2c(pBtCoexist, 0x6E, 1, H2C_Parameter);
	} else
		pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x765, 0x18);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_IS_IN_MP_MODE, &bIsInMpMode);
	if (!bIsInMpMode)
		pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x67, 0x20, 0x0); /* BT select s0/s1 is controlled by BT */
	else
		pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x67, 0x20, 0x1); /* BT select s0/s1 is controlled by WiFi */
}