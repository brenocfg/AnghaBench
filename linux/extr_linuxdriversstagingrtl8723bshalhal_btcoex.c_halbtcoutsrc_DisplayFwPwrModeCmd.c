#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/ * pwrModeVal; int /*<<< orphan*/ * cliBuf; } ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  BT_TMP_BUF_SIZE ; 
 int /*<<< orphan*/  CL_PRINTF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CL_SPRINTF (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void halbtcoutsrc_DisplayFwPwrModeCmd(PBTC_COEXIST pBtCoexist)
{
	u8 *cliBuf = pBtCoexist->cliBuf;

	CL_SPRINTF(cliBuf, BT_TMP_BUF_SIZE, "\r\n %-35s = %02x %02x %02x %02x %02x %02x ", "Power mode cmd ", \
		pBtCoexist->pwrModeVal[0], pBtCoexist->pwrModeVal[1],
		pBtCoexist->pwrModeVal[2], pBtCoexist->pwrModeVal[3],
		pBtCoexist->pwrModeVal[4], pBtCoexist->pwrModeVal[5]);
	CL_PRINTF(cliBuf);
}