#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hal_btcoex_RecordPwrMode (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void rtw_btcoex_RecordPwrMode(struct adapter *padapter, u8 *pCmdBuf, u8 cmdLen)
{
	hal_btcoex_RecordPwrMode(padapter, pCmdBuf, cmdLen);
}