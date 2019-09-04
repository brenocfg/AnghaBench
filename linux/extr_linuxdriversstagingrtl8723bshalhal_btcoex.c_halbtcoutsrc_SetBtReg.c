#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct adapter {int dummy; } ;
struct TYPE_2__ {struct adapter* Adapter; } ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rtw_hal_fill_h2c_cmd (struct adapter*,int,int,int*) ; 

__attribute__((used)) static void halbtcoutsrc_SetBtReg(void *pBtcContext, u8 RegType, u32 RegAddr, u32 Data)
{
	PBTC_COEXIST pBtCoexist;
	struct adapter *padapter;
	u8 CmdBuffer1[4] = {0};
	u8 CmdBuffer2[4] = {0};
	u8 *AddrToSet = (u8 *)&RegAddr;
	u8 *ValueToSet = (u8 *)&Data;
	u8 OperVer = 0;
	u8 ReqNum = 0;

	pBtCoexist = (PBTC_COEXIST)pBtcContext;
	padapter = pBtCoexist->Adapter;

	CmdBuffer1[0] |= (OperVer & 0x0f);						/* Set OperVer */
	CmdBuffer1[0] |= ((ReqNum << 4) & 0xf0);				/* Set ReqNum */
	CmdBuffer1[1] = 0x0d;									/* Set OpCode to BT_LO_OP_WRITE_REG_VALUE */
	CmdBuffer1[2] = ValueToSet[0];							/* Set WriteRegValue */
	rtw_hal_fill_h2c_cmd(padapter, 0x67, 4, &(CmdBuffer1[0]));

	msleep(200);
	ReqNum++;

	CmdBuffer2[0] |= (OperVer & 0x0f);						/* Set OperVer */
	CmdBuffer2[0] |= ((ReqNum << 4) & 0xf0);				/* Set ReqNum */
	CmdBuffer2[1] = 0x0c;									/* Set OpCode of BT_LO_OP_WRITE_REG_ADDR */
	CmdBuffer2[3] = AddrToSet[0];							/* Set WriteRegAddr */
	rtw_hal_fill_h2c_cmd(padapter, 0x67, 4, &(CmdBuffer2[0]));
}