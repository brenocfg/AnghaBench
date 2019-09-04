#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_28__ {scalar_t__ btdmAntPos; } ;
struct TYPE_27__ {int (* fBtcRead4Byte ) (TYPE_1__*,int) ;int /*<<< orphan*/  (* fBtcWrite4Byte ) (TYPE_1__*,int,int) ;int /*<<< orphan*/  (* fBtcWrite1ByteBitMask ) (TYPE_1__*,int,int,int) ;int /*<<< orphan*/  (* fBtcFillH2c ) (TYPE_1__*,int,int,int*) ;int /*<<< orphan*/  (* fBtcSetBtReg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  (* fBtcSetRfReg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ;int /*<<< orphan*/  (* fBtcWrite1Byte ) (TYPE_1__*,int,int) ;int /*<<< orphan*/  (* fBtcGet ) (TYPE_1__*,int /*<<< orphan*/ ,int*) ;TYPE_2__ boardInfo; } ;
typedef  TYPE_1__* PBTC_COEXIST ;
typedef  TYPE_2__* PBTC_BOARD_INFO ;

/* Variables and functions */
 int BIT23 ; 
 int BIT24 ; 
 scalar_t__ BTC_ANTENNA_AT_MAIN_PORT ; 
#define  BTC_ANT_WIFI_AT_AUX 129 
#define  BTC_ANT_WIFI_AT_MAIN 128 
 int /*<<< orphan*/  BTC_BT_REG_RF ; 
 int /*<<< orphan*/  BTC_GET_BL_EXT_SWITCH ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_FW_VER ; 
 int /*<<< orphan*/  BTC_RF_A ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub10 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub11 (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub12 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub13 (TYPE_1__*,int,int,int*) ; 
 int stub14 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub15 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub16 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub17 (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  stub18 (TYPE_1__*,int,int,int) ; 
 int stub19 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub20 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub21 (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  stub22 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub23 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub7 (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  stub8 (TYPE_1__*,int,int,int*) ; 
 int /*<<< orphan*/  stub9 (TYPE_1__*,int,int) ; 

__attribute__((used)) static void halbtc8723b2ant_SetAntPath(
	PBTC_COEXIST pBtCoexist, u8 antPosType, bool bInitHwCfg, bool bWifiOff
)
{
	PBTC_BOARD_INFO pBoardInfo = &pBtCoexist->boardInfo;
	u32 fwVer = 0, u4Tmp = 0;
	bool bPgExtSwitch = false;
	bool bUseExtSwitch = false;
	u8 	H2C_Parameter[2] = {0};

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_EXT_SWITCH, &bPgExtSwitch);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_FW_VER, &fwVer);	/*  [31:16]=fw ver, [15:0]=fw sub ver */

	if ((fwVer > 0 && fwVer < 0xc0000) || bPgExtSwitch)
		bUseExtSwitch = true;

	if (bInitHwCfg) {
		pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x39, 0x8, 0x1);
		pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x974, 0xff);
		pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x944, 0x3, 0x3);
		pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x930, 0x77);
		pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x67, 0x20, 0x1);

		if (fwVer >= 0x180000) {
			/* Use H2C to set GNT_BT to LOW */
			H2C_Parameter[0] = 0;
			pBtCoexist->fBtcFillH2c(pBtCoexist, 0x6E, 1, H2C_Parameter);
		} else {
			pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x765, 0x0);
		}

		pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x0);

		pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0); /* WiFi TRx Mask off */
		pBtCoexist->fBtcSetBtReg(pBtCoexist, BTC_BT_REG_RF, 0x3c, 0x01); /* BT TRx Mask off */

		if (pBoardInfo->btdmAntPos == BTC_ANTENNA_AT_MAIN_PORT) {
			/* tell firmware "no antenna inverse" */
			H2C_Parameter[0] = 0;
		} else {
			/* tell firmware "antenna inverse" */
			H2C_Parameter[0] = 1;
		}

		if (bUseExtSwitch) {
			/* ext switch type */
			H2C_Parameter[1] = 1;
		} else {
			/* int switch type */
			H2C_Parameter[1] = 0;
		}
		pBtCoexist->fBtcFillH2c(pBtCoexist, 0x65, 2, H2C_Parameter);
	}

	/*  ext switch setting */
	if (bUseExtSwitch) {
		if (bInitHwCfg) {
			/*  0x4c[23]= 0, 0x4c[24]= 1  Antenna control by WL/BT */
			u4Tmp = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x4c);
			u4Tmp &= ~BIT23;
			u4Tmp |= BIT24;
			pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x4c, u4Tmp);
		}

		pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x0); /*  fixed internal switch S1->WiFi, S0->BT */
		switch (antPosType) {
		case BTC_ANT_WIFI_AT_MAIN:
			pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x92c, 0x3, 0x1);	/*  ext switch main at wifi */
			break;
		case BTC_ANT_WIFI_AT_AUX:
			pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x92c, 0x3, 0x2);	/*  ext switch aux at wifi */
			break;
		}
	} else { /*  internal switch */
		if (bInitHwCfg) {
			/*  0x4c[23]= 0, 0x4c[24]= 1  Antenna control by WL/BT */
			u4Tmp = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x4c);
			u4Tmp |= BIT23;
			u4Tmp &= ~BIT24;
			pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x4c, u4Tmp);
		}

		pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x64, 0x1, 0x0); /* fixed external switch S1->Main, S0->Aux */
		switch (antPosType) {
		case BTC_ANT_WIFI_AT_MAIN:
			pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x0); /*  fixed internal switch S1->WiFi, S0->BT */
			break;
		case BTC_ANT_WIFI_AT_AUX:
			pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x280); /*  fixed internal switch S0->WiFi, S1->BT */
			break;
		}
	}
}