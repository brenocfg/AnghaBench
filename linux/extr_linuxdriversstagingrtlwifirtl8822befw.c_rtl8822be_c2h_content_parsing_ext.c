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
struct TYPE_2__ {struct rtl_halmac_ops* ops; } ;
struct rtl_priv {TYPE_1__ halmac; } ;
struct rtl_halmac_ops {int /*<<< orphan*/  (* halmac_c2h_handle ) (struct rtl_priv*,int*,int /*<<< orphan*/ ) ;} ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_FW ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_tx_report_handler (struct ieee80211_hw*,int*,int) ; 
 int /*<<< orphan*/  stub1 (struct rtl_priv*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void rtl8822be_c2h_content_parsing_ext(struct ieee80211_hw *hw,
				       u8 c2h_sub_cmd_id,
				       u8 c2h_cmd_len,
				       u8 *c2h_content_buf)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_halmac_ops *halmac_ops;

	switch (c2h_sub_cmd_id) {
	case 0x0F:
		RT_TRACE(rtlpriv, COMP_FW, DBG_TRACE,
			 "[C2H], C2H_8822BE_TX_REPORT!\n");
		rtl_tx_report_handler(hw, c2h_content_buf, c2h_cmd_len);
		break;
	default:
		/* indicate c2h pkt + rx desc to halmac */
		halmac_ops = rtlpriv->halmac.ops;
		halmac_ops->halmac_c2h_handle(rtlpriv,
					      c2h_content_buf - 24 - 2 - 2,
					      c2h_cmd_len + 24 + 2 + 2);
		break;
	}
}