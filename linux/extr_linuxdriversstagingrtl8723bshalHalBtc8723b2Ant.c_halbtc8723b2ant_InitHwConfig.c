#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_13__ {int /*<<< orphan*/  btRf0x1eBackup; } ;
struct TYPE_12__ {int (* fBtcRead1Byte ) (TYPE_1__*,int) ;int /*<<< orphan*/  (* fBtcWrite1ByteBitMask ) (TYPE_1__*,int,int,int) ;int /*<<< orphan*/  (* fBtcWrite1Byte ) (TYPE_1__*,int,int) ;int /*<<< orphan*/  (* fBtcGetRfReg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;} ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_WIFI_AT_MAIN ; 
 int /*<<< orphan*/  BTC_MSG_INTERFACE ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BTC_RF_A ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  INTF_INIT ; 
 int /*<<< orphan*/  halbtc8723b2ant_CoexTableWithType (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8723b2ant_SetAntPath (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_8__* pCoexDm ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__*,int,int,int) ; 

__attribute__((used)) static void halbtc8723b2ant_InitHwConfig(PBTC_COEXIST pBtCoexist, bool bBackUp)
{
	u8 u1Tmp = 0;

	BTC_PRINT(BTC_MSG_INTERFACE, INTF_INIT, ("[BTCoex], 2Ant Init HW Config!!\n"));

	/*  backup rf 0x1e value */
	pCoexDm->btRf0x1eBackup =
		pBtCoexist->fBtcGetRfReg(pBtCoexist, BTC_RF_A, 0x1e, 0xfffff);

	/*  0x790[5:0]= 0x5 */
	u1Tmp = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x790);
	u1Tmp &= 0xc0;
	u1Tmp |= 0x5;
	pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x790, u1Tmp);

	/* Antenna config */
	halbtc8723b2ant_SetAntPath(pBtCoexist, BTC_ANT_WIFI_AT_MAIN, true, false);

	/*  PTA parameter */
	halbtc8723b2ant_CoexTableWithType(pBtCoexist, FORCE_EXEC, 0);

	/*  Enable counter statistics */
	pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x76e, 0xc); /* 0x76e[3] = 1, WLAN_Act control by PTA */
	pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x778, 0x3);
	pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x40, 0x20, 0x1);
}