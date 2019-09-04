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
typedef  int u16 ;
struct btinfo {int cid; int len; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_btcoex_BtInfoNotify (struct adapter*,int,int*) ; 
 int /*<<< orphan*/  rtw_warn_on (int) ; 

__attribute__((used)) static void rtw_btinfo_hdl(struct adapter *adapter, u8 *buf, u16 buf_len)
{
	#define BTINFO_WIFI_FETCH 0x23
	#define BTINFO_BT_AUTO_RPT 0x27
	struct btinfo *info = (struct btinfo *)buf;
	u8 cmd_idx;
	u8 len;

	cmd_idx = info->cid;

	if (info->len > buf_len-2) {
		rtw_warn_on(1);
		len = buf_len-2;
	} else {
		len = info->len;
	}

/* define DBG_PROC_SET_BTINFO_EVT */
#ifdef DBG_PROC_SET_BTINFO_EVT
	btinfo_evt_dump(RTW_DBGDUMP, info);
#endif

	/* transform BT-FW btinfo to WiFI-FW C2H format and notify */
	if (cmd_idx == BTINFO_WIFI_FETCH)
		buf[1] = 0;
	else if (cmd_idx == BTINFO_BT_AUTO_RPT)
		buf[1] = 2;
	rtw_btcoex_BtInfoNotify(adapter, len+1, &buf[1]);
}