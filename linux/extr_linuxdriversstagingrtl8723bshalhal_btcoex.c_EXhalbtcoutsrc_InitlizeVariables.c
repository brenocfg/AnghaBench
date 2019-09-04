#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {scalar_t__ singleAntPath; } ;
struct TYPE_5__ {TYPE_1__ boardInfo; int /*<<< orphan*/ * cliBuf; int /*<<< orphan*/  fBtcSetBtReg; int /*<<< orphan*/  fBtcGetBtReg; int /*<<< orphan*/  fBtcSet; int /*<<< orphan*/  fBtcGet; int /*<<< orphan*/  fBtcDispDbgMsg; int /*<<< orphan*/  fBtcFillH2c; int /*<<< orphan*/  fBtcGetRfReg; int /*<<< orphan*/  fBtcSetRfReg; int /*<<< orphan*/  fBtcGetBbReg; int /*<<< orphan*/  fBtcSetBbReg; int /*<<< orphan*/  fBtcWriteLocalReg1Byte; int /*<<< orphan*/  fBtcWrite4Byte; int /*<<< orphan*/  fBtcRead4Byte; int /*<<< orphan*/  fBtcWrite2Byte; int /*<<< orphan*/  fBtcRead2Byte; int /*<<< orphan*/  fBtcWrite1ByteBitMask; int /*<<< orphan*/  fBtcWrite1Byte; int /*<<< orphan*/  fBtcRead1Byte; int /*<<< orphan*/  chipInterface; } ;
typedef  TYPE_2__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_INTF_SDIO ; 
 int /*<<< orphan*/  EXhalbtcoutsrc_BindBtCoexWithAdapter (void*) ; 
 TYPE_2__ GLBtCoexist ; 
 int /*<<< orphan*/ * GLBtcDbgBuf ; 
 int GLBtcWiFiInIQKState ; 
 int GLBtcWiFiInScanState ; 
 int /*<<< orphan*/  halbtcoutsrc_BitMaskWrite1Byte ; 
 int /*<<< orphan*/  halbtcoutsrc_DbgInit () ; 
 int /*<<< orphan*/  halbtcoutsrc_DisplayDbgMsg ; 
 int /*<<< orphan*/  halbtcoutsrc_FillH2cCmd ; 
 int /*<<< orphan*/  halbtcoutsrc_Get ; 
 int /*<<< orphan*/  halbtcoutsrc_GetBbReg ; 
 int /*<<< orphan*/  halbtcoutsrc_GetBtReg ; 
 int /*<<< orphan*/  halbtcoutsrc_GetRfReg ; 
 int /*<<< orphan*/  halbtcoutsrc_Read1Byte ; 
 int /*<<< orphan*/  halbtcoutsrc_Read2Byte ; 
 int /*<<< orphan*/  halbtcoutsrc_Read4Byte ; 
 int /*<<< orphan*/  halbtcoutsrc_Set ; 
 int /*<<< orphan*/  halbtcoutsrc_SetBbReg ; 
 int /*<<< orphan*/  halbtcoutsrc_SetBtReg ; 
 int /*<<< orphan*/  halbtcoutsrc_SetRfReg ; 
 int /*<<< orphan*/  halbtcoutsrc_Write1Byte ; 
 int /*<<< orphan*/  halbtcoutsrc_Write2Byte ; 
 int /*<<< orphan*/  halbtcoutsrc_Write4Byte ; 
 int /*<<< orphan*/  halbtcoutsrc_WriteLocalReg1Byte ; 

u8 EXhalbtcoutsrc_InitlizeVariables(void *padapter)
{
	PBTC_COEXIST pBtCoexist = &GLBtCoexist;

	/* pBtCoexist->statistics.cntBind++; */

	halbtcoutsrc_DbgInit();

	pBtCoexist->chipInterface = BTC_INTF_SDIO;

	EXhalbtcoutsrc_BindBtCoexWithAdapter(padapter);

	pBtCoexist->fBtcRead1Byte = halbtcoutsrc_Read1Byte;
	pBtCoexist->fBtcWrite1Byte = halbtcoutsrc_Write1Byte;
	pBtCoexist->fBtcWrite1ByteBitMask = halbtcoutsrc_BitMaskWrite1Byte;
	pBtCoexist->fBtcRead2Byte = halbtcoutsrc_Read2Byte;
	pBtCoexist->fBtcWrite2Byte = halbtcoutsrc_Write2Byte;
	pBtCoexist->fBtcRead4Byte = halbtcoutsrc_Read4Byte;
	pBtCoexist->fBtcWrite4Byte = halbtcoutsrc_Write4Byte;
	pBtCoexist->fBtcWriteLocalReg1Byte = halbtcoutsrc_WriteLocalReg1Byte;

	pBtCoexist->fBtcSetBbReg = halbtcoutsrc_SetBbReg;
	pBtCoexist->fBtcGetBbReg = halbtcoutsrc_GetBbReg;

	pBtCoexist->fBtcSetRfReg = halbtcoutsrc_SetRfReg;
	pBtCoexist->fBtcGetRfReg = halbtcoutsrc_GetRfReg;

	pBtCoexist->fBtcFillH2c = halbtcoutsrc_FillH2cCmd;
	pBtCoexist->fBtcDispDbgMsg = halbtcoutsrc_DisplayDbgMsg;

	pBtCoexist->fBtcGet = halbtcoutsrc_Get;
	pBtCoexist->fBtcSet = halbtcoutsrc_Set;
	pBtCoexist->fBtcGetBtReg = halbtcoutsrc_GetBtReg;
	pBtCoexist->fBtcSetBtReg = halbtcoutsrc_SetBtReg;

	pBtCoexist->cliBuf = &GLBtcDbgBuf[0];

	pBtCoexist->boardInfo.singleAntPath = 0;

	GLBtcWiFiInScanState = false;

	GLBtcWiFiInIQKState = false;

	return true;
}