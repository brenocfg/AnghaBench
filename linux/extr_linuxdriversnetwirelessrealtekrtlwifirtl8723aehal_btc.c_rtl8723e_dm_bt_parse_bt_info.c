#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_3__ {int bt_busy; int /*<<< orphan*/  cstate; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {int c2h_bt_info_req_sent; size_t bt_retry_cnt; size_t c2h_bt_info_original; int c2h_bt_inquiry_page; } ;

/* Variables and functions */
 size_t BIT (int) ; 
 size_t BTINFO_B_CONNECTION ; 
 int /*<<< orphan*/  BT_COEX_STATE_BT_IDLE ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__ hal_coex_8723 ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8723e_dm_bt_parse_bt_info(struct ieee80211_hw *hw,
					 u8 *tmp_buf, u8 len)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 bt_info;
	u8 i;

	hal_coex_8723.c2h_bt_info_req_sent = false;
	hal_coex_8723.bt_retry_cnt = 0;
	for (i = 0; i < len; i++) {
		if (i == 0)
			hal_coex_8723.c2h_bt_info_original = tmp_buf[i];
		else if (i == 1)
			hal_coex_8723.bt_retry_cnt = tmp_buf[i];
		if (i == len-1)
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				 "0x%2x]", tmp_buf[i]);
		else
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				 "0x%2x, ", tmp_buf[i]);

	}
	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
		"BT info bt_info (Data)= 0x%x\n",
			hal_coex_8723.c2h_bt_info_original);
	bt_info = hal_coex_8723.c2h_bt_info_original;

	if (bt_info & BIT(2))
		hal_coex_8723.c2h_bt_inquiry_page = true;
	else
		hal_coex_8723.c2h_bt_inquiry_page = false;


	if (bt_info & BTINFO_B_CONNECTION) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTC2H], BTInfo: bConnect=true\n");
		rtlpriv->btcoexist.bt_busy = true;
		rtlpriv->btcoexist.cstate &= ~BT_COEX_STATE_BT_IDLE;
	} else {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTC2H], BTInfo: bConnect=false\n");
		rtlpriv->btcoexist.bt_busy = false;
		rtlpriv->btcoexist.cstate |= BT_COEX_STATE_BT_IDLE;
	}
}