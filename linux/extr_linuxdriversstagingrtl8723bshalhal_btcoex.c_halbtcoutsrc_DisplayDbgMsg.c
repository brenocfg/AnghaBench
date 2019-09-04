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
typedef  int u8 ;
typedef  scalar_t__ PBTC_COEXIST ;

/* Variables and functions */
#define  BTC_DBG_DISP_BT_LINK_INFO 130 
#define  BTC_DBG_DISP_COEX_STATISTICS 129 
#define  BTC_DBG_DISP_FW_PWR_MODE_CMD 128 
 int /*<<< orphan*/  halbtcoutsrc_DisplayFwPwrModeCmd (scalar_t__) ; 

__attribute__((used)) static void halbtcoutsrc_DisplayDbgMsg(void *pBtcContext, u8 dispType)
{
	PBTC_COEXIST pBtCoexist;


	pBtCoexist = (PBTC_COEXIST)pBtcContext;
	switch (dispType) {
	case BTC_DBG_DISP_COEX_STATISTICS:
		break;
	case BTC_DBG_DISP_BT_LINK_INFO:
		break;
	case BTC_DBG_DISP_FW_PWR_MODE_CMD:
		halbtcoutsrc_DisplayFwPwrModeCmd(pBtCoexist);
		break;
	default:
		break;
	}
}