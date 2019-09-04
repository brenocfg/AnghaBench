#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_10__ {TYPE_4__* ops; } ;
struct TYPE_6__ {struct rtl_btc_ops* btc_ops; } ;
struct rtl_priv {TYPE_5__ phydm; TYPE_3__* cfg; TYPE_1__ btcoexist; } ;
struct rtl_btc_ops {int /*<<< orphan*/  (* btc_btmpinfo_notify ) (struct rtl_priv*,int*,int) ;int /*<<< orphan*/  (* btc_btinfo_notify ) (struct rtl_priv*,int*,int) ;} ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* phydm_c2h_content_parsing ) (struct rtl_priv*,int,int,int*) ;} ;
struct TYPE_8__ {TYPE_2__* ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* get_btc_status ) () ;} ;

/* Variables and functions */
#define  C2H_8822B_BT_INFO 131 
#define  C2H_8822B_BT_MP 130 
#define  C2H_8822B_DBG 129 
#define  C2H_8822B_TXBF 128 
 int /*<<< orphan*/  COMP_FW ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  rtl8822be_c2h_content_parsing_ext (struct ieee80211_hw*,int,int,int*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 (struct rtl_priv*,int*,int) ; 
 int /*<<< orphan*/  stub3 () ; 
 int /*<<< orphan*/  stub4 (struct rtl_priv*,int*,int) ; 
 int /*<<< orphan*/  stub5 (struct rtl_priv*,int,int,int*) ; 

void rtl8822be_c2h_content_parsing(struct ieee80211_hw *hw, u8 c2h_cmd_id,
				   u8 c2h_cmd_len, u8 *tmp_buf)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_btc_ops *btc_ops = rtlpriv->btcoexist.btc_ops;

	if (c2h_cmd_id == 0xFF) {
		rtl8822be_c2h_content_parsing_ext(hw, tmp_buf[0],
						  c2h_cmd_len - 2,
						  tmp_buf + 2);
		return;
	}

	switch (c2h_cmd_id) {
	case C2H_8822B_DBG:
		RT_TRACE(rtlpriv, COMP_FW, DBG_TRACE,
			 "[C2H], C2H_8822BE_DBG!!\n");
		break;
	case C2H_8822B_TXBF:
		RT_TRACE(rtlpriv, COMP_FW, DBG_TRACE,
			 "[C2H], C2H_8822B_TXBF!!\n");
		break;
	case C2H_8822B_BT_INFO:
		RT_TRACE(rtlpriv, COMP_FW, DBG_TRACE,
			 "[C2H], C2H_8822BE_BT_INFO!!\n");
		if (rtlpriv->cfg->ops->get_btc_status())
			btc_ops->btc_btinfo_notify(rtlpriv, tmp_buf,
						   c2h_cmd_len);
		break;
	case C2H_8822B_BT_MP:
		RT_TRACE(rtlpriv, COMP_FW, DBG_TRACE,
			 "[C2H], C2H_8822BE_BT_MP!!\n");
		if (rtlpriv->cfg->ops->get_btc_status())
			btc_ops->btc_btmpinfo_notify(rtlpriv, tmp_buf,
						     c2h_cmd_len);
		break;
	default:
		if (!rtlpriv->phydm.ops->phydm_c2h_content_parsing(
			    rtlpriv, c2h_cmd_id, c2h_cmd_len, tmp_buf))
			break;

		RT_TRACE(rtlpriv, COMP_FW, DBG_TRACE,
			 "[C2H], Unknown packet!! CmdId(%#X)!\n", c2h_cmd_id);
		break;
	}
}