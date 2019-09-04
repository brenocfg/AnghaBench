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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_10__ {int txbytesunicast; int rxbytesunicast; } ;
struct TYPE_9__ {int current_turbo_edca; int is_any_nonbepkts; int is_cur_rdlstate; int /*<<< orphan*/  disable_framebursting; } ;
struct TYPE_6__ {scalar_t__ bt_edca_ul; scalar_t__ bt_edca_dl; } ;
struct rtl_priv {TYPE_5__ stats; TYPE_4__ dm; TYPE_3__* cfg; TYPE_1__ btcoexist; } ;
struct rtl_mac {scalar_t__ link_state; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_8__ {TYPE_2__* ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* set_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AC0_BE ; 
 int /*<<< orphan*/  HW_VAR_AC_PARAM ; 
 scalar_t__ MAC80211_LINKED ; 
 int /*<<< orphan*/  REG_EDCA_BE_PARAM ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtl88e_dm_check_edca_turbo(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	static u64 last_txok_cnt;
	static u64 last_rxok_cnt;
	static u32 last_bt_edca_ul;
	static u32 last_bt_edca_dl;
	u64 cur_txok_cnt = 0;
	u64 cur_rxok_cnt = 0;
	u32 edca_be_ul = 0x5ea42b;
	u32 edca_be_dl = 0x5ea42b;
	bool bt_change_edca = false;

	if ((last_bt_edca_ul != rtlpriv->btcoexist.bt_edca_ul) ||
	    (last_bt_edca_dl != rtlpriv->btcoexist.bt_edca_dl)) {
		rtlpriv->dm.current_turbo_edca = false;
		last_bt_edca_ul = rtlpriv->btcoexist.bt_edca_ul;
		last_bt_edca_dl = rtlpriv->btcoexist.bt_edca_dl;
	}

	if (rtlpriv->btcoexist.bt_edca_ul != 0) {
		edca_be_ul = rtlpriv->btcoexist.bt_edca_ul;
		bt_change_edca = true;
	}

	if (rtlpriv->btcoexist.bt_edca_dl != 0) {
		edca_be_ul = rtlpriv->btcoexist.bt_edca_dl;
		bt_change_edca = true;
	}

	if (mac->link_state != MAC80211_LINKED) {
		rtlpriv->dm.current_turbo_edca = false;
		return;
	}
	if ((bt_change_edca) ||
	    ((!rtlpriv->dm.is_any_nonbepkts) &&
	     (!rtlpriv->dm.disable_framebursting))) {

		cur_txok_cnt = rtlpriv->stats.txbytesunicast - last_txok_cnt;
		cur_rxok_cnt = rtlpriv->stats.rxbytesunicast - last_rxok_cnt;

		if (cur_rxok_cnt > 4 * cur_txok_cnt) {
			if (!rtlpriv->dm.is_cur_rdlstate ||
			    !rtlpriv->dm.current_turbo_edca) {
				rtl_write_dword(rtlpriv,
						REG_EDCA_BE_PARAM,
						edca_be_dl);
				rtlpriv->dm.is_cur_rdlstate = true;
			}
		} else {
			if (rtlpriv->dm.is_cur_rdlstate ||
			    !rtlpriv->dm.current_turbo_edca) {
				rtl_write_dword(rtlpriv,
						REG_EDCA_BE_PARAM,
						edca_be_ul);
				rtlpriv->dm.is_cur_rdlstate = false;
			}
		}
		rtlpriv->dm.current_turbo_edca = true;
	} else {
		if (rtlpriv->dm.current_turbo_edca) {
			u8 tmp = AC0_BE;

			rtlpriv->cfg->ops->set_hw_reg(hw,
						      HW_VAR_AC_PARAM,
						      &tmp);
			rtlpriv->dm.current_turbo_edca = false;
		}
	}

	rtlpriv->dm.is_any_nonbepkts = false;
	last_txok_cnt = rtlpriv->stats.txbytesunicast;
	last_rxok_cnt = rtlpriv->stats.rxbytesunicast;
}