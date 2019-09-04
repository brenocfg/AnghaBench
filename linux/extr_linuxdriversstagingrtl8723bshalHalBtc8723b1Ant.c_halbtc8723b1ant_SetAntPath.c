#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_53__   TYPE_2__ ;
typedef  struct TYPE_52__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_53__ {scalar_t__ btdmAntPos; } ;
struct TYPE_52__ {int (* fBtcRead4Byte ) (TYPE_1__*,int) ;int (* fBtcRead1Byte ) (TYPE_1__*,int) ;int /*<<< orphan*/  (* fBtcWrite4Byte ) (TYPE_1__*,int,int) ;int /*<<< orphan*/  (* fBtcFillH2c ) (TYPE_1__*,int,int,int*) ;int /*<<< orphan*/  (* fBtcWrite1ByteBitMask ) (TYPE_1__*,int,int,int) ;int /*<<< orphan*/  (* fBtcWrite1Byte ) (TYPE_1__*,int,int) ;int /*<<< orphan*/  (* fBtcGet ) (TYPE_1__*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* fBtcSetBtReg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  (* fBtcSetRfReg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ;TYPE_2__ boardInfo; } ;
typedef  TYPE_1__* PBTC_COEXIST ;
typedef  TYPE_2__* PBTC_BOARD_INFO ;

/* Variables and functions */
 int BIT0 ; 
 int BIT23 ; 
 int BIT24 ; 
 scalar_t__ BTC_ANTENNA_AT_MAIN_PORT ; 
#define  BTC_ANT_PATH_BT 130 
#define  BTC_ANT_PATH_PTA 129 
#define  BTC_ANT_PATH_WIFI 128 
 int /*<<< orphan*/  BTC_BT_REG_RF ; 
 int /*<<< orphan*/  BTC_GET_BL_EXT_SWITCH ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_IS_IN_MP_MODE ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_FW_VER ; 
 int /*<<< orphan*/  BTC_MSG_INTERFACE ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BTC_RF_A ; 
 int /*<<< orphan*/  INTF_INIT ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub10 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub11 (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  stub12 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub13 (TYPE_1__*,int,int,int*) ; 
 int /*<<< orphan*/  stub14 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub15 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub16 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub17 (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  stub18 (TYPE_1__*,int,int,int) ; 
 int stub19 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub20 (TYPE_1__*,int,int) ; 
 int stub21 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub22 (TYPE_1__*,int,int,int*) ; 
 int stub23 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub24 (TYPE_1__*,int,int) ; 
 int stub25 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub26 (TYPE_1__*,int,int) ; 
 int stub27 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub28 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub29 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub30 (TYPE_1__*,int,int,int*) ; 
 int /*<<< orphan*/  stub31 (TYPE_1__*,int,int,int*) ; 
 int /*<<< orphan*/  stub32 (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  stub33 (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  stub34 (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  stub35 (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  stub36 (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  stub37 (TYPE_1__*,int,int,int) ; 
 int stub38 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub39 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub40 (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  stub41 (TYPE_1__*,int,int,int*) ; 
 int /*<<< orphan*/  stub42 (TYPE_1__*,int,int,int*) ; 
 int /*<<< orphan*/  stub43 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub44 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub45 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub46 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub47 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub48 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__*,int,int,int*) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub7 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub8 (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  stub9 (TYPE_1__*,int,int,int) ; 

__attribute__((used)) static void halbtc8723b1ant_SetAntPath(
	PBTC_COEXIST pBtCoexist, u8 antPosType, bool bInitHwCfg, bool bWifiOff
)
{
	PBTC_BOARD_INFO pBoardInfo = &pBtCoexist->boardInfo;
	u32 fwVer = 0, u4Tmp = 0, cntBtCalChk = 0;
	bool bPgExtSwitch = false;
	bool bUseExtSwitch = false;
	bool bIsInMpMode = false;
	u8 H2C_Parameter[2] = {0}, u1Tmp = 0;

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_EXT_SWITCH, &bPgExtSwitch);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_FW_VER, &fwVer); /*  [31:16]=fw ver, [15:0]=fw sub ver */

	if ((fwVer > 0 && fwVer < 0xc0000) || bPgExtSwitch)
		bUseExtSwitch = true;

	if (bInitHwCfg) {
		pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x780); /* WiFi TRx Mask on */
		pBtCoexist->fBtcSetBtReg(pBtCoexist, BTC_BT_REG_RF, 0x3c, 0x15); /* BT TRx Mask on */

		if (fwVer >= 0x180000) {
			/* Use H2C to set GNT_BT to HIGH */
			H2C_Parameter[0] = 1;
			pBtCoexist->fBtcFillH2c(pBtCoexist, 0x6E, 1, H2C_Parameter);
		} else /*  set grant_bt to high */
			pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x765, 0x18);

		/* set wlan_act control by PTA */
		pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x76e, 0x4);

		pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x67, 0x20, 0x1); /* BT select s0/s1 is controlled by WiFi */

		pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x39, 0x8, 0x1);
		pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x974, 0xff);
		pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x944, 0x3, 0x3);
		pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x930, 0x77);
	} else if (bWifiOff) {
		if (fwVer >= 0x180000) {
			/* Use H2C to set GNT_BT to HIGH */
			H2C_Parameter[0] = 1;
			pBtCoexist->fBtcFillH2c(pBtCoexist, 0x6E, 1, H2C_Parameter);
		} else /*  set grant_bt to high */
			pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x765, 0x18);

		/* set wlan_act to always low */
		pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x76e, 0x4);

		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_IS_IN_MP_MODE, &bIsInMpMode);
		if (!bIsInMpMode)
			pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x67, 0x20, 0x0); /* BT select s0/s1 is controlled by BT */
		else
			pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x67, 0x20, 0x1); /* BT select s0/s1 is controlled by WiFi */

		/*  0x4c[24:23]= 00, Set Antenna control by BT_RFE_CTRL	BT Vendor 0xac = 0xf002 */
		u4Tmp = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x4c);
		u4Tmp &= ~BIT23;
		u4Tmp &= ~BIT24;
		pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x4c, u4Tmp);
	} else {
		/* Use H2C to set GNT_BT to LOW */
		if (fwVer >= 0x180000) {
			if (pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x765) != 0) {
				H2C_Parameter[0] = 0;
				pBtCoexist->fBtcFillH2c(pBtCoexist, 0x6E, 1, H2C_Parameter);
			}
		} else {
			/*  BT calibration check */
			while (cntBtCalChk <= 20) {
				u1Tmp = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x49d);
				cntBtCalChk++;

				if (u1Tmp & BIT0) {
					BTC_PRINT(BTC_MSG_INTERFACE, INTF_INIT, ("[BTCoex], ########### BT is calibrating (wait cnt =%d) ###########\n", cntBtCalChk));
					mdelay(50);
				} else {
					BTC_PRINT(BTC_MSG_INTERFACE, INTF_INIT, ("[BTCoex], ********** BT is NOT calibrating (wait cnt =%d)**********\n", cntBtCalChk));
					break;
				}
			}

			/*  set grant_bt to PTA */
			pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x765, 0x0);
		}

		if (pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x76e) != 0xc)
			/* set wlan_act control by PTA */
			pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x76e, 0xc);
	}

	if (bUseExtSwitch) {
		if (bInitHwCfg) {
			/*  0x4c[23]= 0, 0x4c[24]= 1  Antenna control by WL/BT */
			u4Tmp = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x4c);
			u4Tmp &= ~BIT23;
			u4Tmp |= BIT24;
			pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x4c, u4Tmp);

			pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x0); /*  fixed internal switch S1->WiFi, S0->BT */

			if (pBoardInfo->btdmAntPos == BTC_ANTENNA_AT_MAIN_PORT) {
				/* tell firmware "no antenna inverse" */
				H2C_Parameter[0] = 0;
				H2C_Parameter[1] = 1;  /* ext switch type */
				pBtCoexist->fBtcFillH2c(pBtCoexist, 0x65, 2, H2C_Parameter);
			} else {
				/* tell firmware "antenna inverse" */
				H2C_Parameter[0] = 1;
				H2C_Parameter[1] = 1;  /* ext switch type */
				pBtCoexist->fBtcFillH2c(pBtCoexist, 0x65, 2, H2C_Parameter);
			}
		}


		/*  ext switch setting */
		switch (antPosType) {
		case BTC_ANT_PATH_WIFI:
			if (pBoardInfo->btdmAntPos == BTC_ANTENNA_AT_MAIN_PORT)
				pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x92c, 0x3, 0x1);
			else
				pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x92c, 0x3, 0x2);
			break;
		case BTC_ANT_PATH_BT:
			if (pBoardInfo->btdmAntPos == BTC_ANTENNA_AT_MAIN_PORT)
				pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x92c, 0x3, 0x2);
			else
				pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x92c, 0x3, 0x1);
			break;
		default:
		case BTC_ANT_PATH_PTA:
			if (pBoardInfo->btdmAntPos == BTC_ANTENNA_AT_MAIN_PORT)
				pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x92c, 0x3, 0x1);
			else
				pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x92c, 0x3, 0x2);
			break;
		}

	} else {
		if (bInitHwCfg) {
			/*  0x4c[23]= 1, 0x4c[24]= 0  Antenna control by 0x64 */
			u4Tmp = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x4c);
			u4Tmp |= BIT23;
			u4Tmp &= ~BIT24;
			pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x4c, u4Tmp);

			/* Fix Ext switch Main->S1, Aux->S0 */
			pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x64, 0x1, 0x0);

			if (pBoardInfo->btdmAntPos == BTC_ANTENNA_AT_MAIN_PORT) {

				/* tell firmware "no antenna inverse" */
				H2C_Parameter[0] = 0;
				H2C_Parameter[1] = 0;  /* internal switch type */
				pBtCoexist->fBtcFillH2c(pBtCoexist, 0x65, 2, H2C_Parameter);
			} else {

				/* tell firmware "antenna inverse" */
				H2C_Parameter[0] = 1;
				H2C_Parameter[1] = 0;  /* internal switch type */
				pBtCoexist->fBtcFillH2c(pBtCoexist, 0x65, 2, H2C_Parameter);
			}
		}


		/*  internal switch setting */
		switch (antPosType) {
		case BTC_ANT_PATH_WIFI:
			if (pBoardInfo->btdmAntPos == BTC_ANTENNA_AT_MAIN_PORT)
				pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x0);
			else
				pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x280);
			break;
		case BTC_ANT_PATH_BT:
			if (pBoardInfo->btdmAntPos == BTC_ANTENNA_AT_MAIN_PORT)
				pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x280);
			else
				pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x0);
			break;
		default:
		case BTC_ANT_PATH_PTA:
			if (pBoardInfo->btdmAntPos == BTC_ANTENNA_AT_MAIN_PORT)
				pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x200);
			else
				pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x80);
			break;
		}
	}
}