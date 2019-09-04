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
struct adapter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pwrModeVal; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALGO_TRACE_FW_EXEC ; 
 int /*<<< orphan*/  BTC_MSG_ALGORITHM ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ GLBtCoexist ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

void hal_btcoex_RecordPwrMode(struct adapter *padapter, u8 *pCmdBuf, u8 cmdLen)
{
	BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_EXEC, ("[BTCoex], FW write pwrModeCmd = 0x%04x%08x\n",
		pCmdBuf[0]<<8|pCmdBuf[1],
		pCmdBuf[2]<<24|pCmdBuf[3]<<16|pCmdBuf[4]<<8|pCmdBuf[5]));

	memcpy(GLBtCoexist.pwrModeVal, pCmdBuf, cmdLen);
}