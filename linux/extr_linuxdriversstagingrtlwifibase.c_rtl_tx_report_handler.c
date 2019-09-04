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
typedef  int u16 ;
struct rtl_tx_report {int last_recv_sn; } ;
struct rtl_priv {TYPE_1__* cfg; struct rtl_tx_report tx_report; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {int spec_ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_TX_REPORT ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int RTL_SPEC_NEW_FW_C2H ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl_tx_report_handler(struct ieee80211_hw *hw, u8 *tmp_buf, u8 c2h_cmd_len)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_tx_report *tx_report = &rtlpriv->tx_report;
	u16 sn;
	u8 st, retry;

	if (rtlpriv->cfg->spec_ver & RTL_SPEC_NEW_FW_C2H) {
		sn = tmp_buf[6];
		st = tmp_buf[7] & 0xC0;
		retry = tmp_buf[8] & 0x3F;
	} else {
		sn = ((tmp_buf[7] & 0x0F) << 8) | tmp_buf[6];
		st = tmp_buf[0] & 0xC0;
		retry = tmp_buf[2] & 0x3F;
	}

	tx_report->last_recv_sn = sn;

	RT_TRACE(rtlpriv, COMP_TX_REPORT, DBG_DMESG,
		 "Recv TX-Report st=0x%02X sn=0x%X retry=0x%X\n",
		 st, sn, retry);
}