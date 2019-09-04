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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_10__ {int txbytesunicast; int rxbytesunicast; } ;
struct TYPE_9__ {int current_turbo_edca; int is_any_nonbepkts; int is_cur_rdlstate; int /*<<< orphan*/  disable_framebursting; } ;
struct TYPE_6__ {scalar_t__ rf_type; } ;
struct rtl_priv {TYPE_5__ stats; TYPE_4__ dm; TYPE_3__* cfg; TYPE_1__ phy; } ;
struct rtl_mac {size_t vendor; scalar_t__ link_state; scalar_t__ mode; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_8__ {TYPE_2__* ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* set_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AC0_BE ; 
 int /*<<< orphan*/  EDCAPARA_BE ; 
 int /*<<< orphan*/  HW_VAR_AC_PARAM ; 
 scalar_t__ MAC80211_LINKED ; 
 scalar_t__ RF_1T2R ; 
 scalar_t__ WIRELESS_MODE_B ; 
 scalar_t__ WIRELESS_MODE_G ; 
 int /*<<< orphan*/ * edca_setting_dl ; 
 int /*<<< orphan*/ * edca_setting_dl_gmode ; 
 int /*<<< orphan*/ * edca_setting_ul ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _rtl92s_dm_check_edca_turbo(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));

	static u64 last_txok_cnt;
	static u64 last_rxok_cnt;
	u64 cur_txok_cnt = 0;
	u64 cur_rxok_cnt = 0;

	u32 edca_be_ul = edca_setting_ul[mac->vendor];
	u32 edca_be_dl = edca_setting_dl[mac->vendor];
	u32 edca_gmode = edca_setting_dl_gmode[mac->vendor];

	if (mac->link_state != MAC80211_LINKED) {
		rtlpriv->dm.current_turbo_edca = false;
		goto dm_checkedcaturbo_exit;
	}

	if ((!rtlpriv->dm.is_any_nonbepkts) &&
	    (!rtlpriv->dm.disable_framebursting)) {
		cur_txok_cnt = rtlpriv->stats.txbytesunicast - last_txok_cnt;
		cur_rxok_cnt = rtlpriv->stats.rxbytesunicast - last_rxok_cnt;

		if (rtlpriv->phy.rf_type == RF_1T2R) {
			if (cur_txok_cnt > 4 * cur_rxok_cnt) {
				/* Uplink TP is present. */
				if (rtlpriv->dm.is_cur_rdlstate ||
					!rtlpriv->dm.current_turbo_edca) {
					rtl_write_dword(rtlpriv, EDCAPARA_BE,
							edca_be_ul);
					rtlpriv->dm.is_cur_rdlstate = false;
				}
			} else {/* Balance TP is present. */
				if (!rtlpriv->dm.is_cur_rdlstate ||
					!rtlpriv->dm.current_turbo_edca) {
					if (mac->mode == WIRELESS_MODE_G ||
					    mac->mode == WIRELESS_MODE_B)
						rtl_write_dword(rtlpriv,
								EDCAPARA_BE,
								edca_gmode);
					else
						rtl_write_dword(rtlpriv,
								EDCAPARA_BE,
								edca_be_dl);
					rtlpriv->dm.is_cur_rdlstate = true;
				}
			}
			rtlpriv->dm.current_turbo_edca = true;
		} else {
			if (cur_rxok_cnt > 4 * cur_txok_cnt) {
				if (!rtlpriv->dm.is_cur_rdlstate ||
					!rtlpriv->dm.current_turbo_edca) {
					if (mac->mode == WIRELESS_MODE_G ||
					    mac->mode == WIRELESS_MODE_B)
						rtl_write_dword(rtlpriv,
								EDCAPARA_BE,
								edca_gmode);
					else
						rtl_write_dword(rtlpriv,
								EDCAPARA_BE,
								edca_be_dl);
					rtlpriv->dm.is_cur_rdlstate = true;
				}
			} else {
				if (rtlpriv->dm.is_cur_rdlstate ||
					!rtlpriv->dm.current_turbo_edca) {
					rtl_write_dword(rtlpriv, EDCAPARA_BE,
							edca_be_ul);
					rtlpriv->dm.is_cur_rdlstate = false;
				}
			}
			rtlpriv->dm.current_turbo_edca = true;
		}
	} else {
		if (rtlpriv->dm.current_turbo_edca) {
			u8 tmp = AC0_BE;
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AC_PARAM,
						      &tmp);
			rtlpriv->dm.current_turbo_edca = false;
		}
	}

dm_checkedcaturbo_exit:
	rtlpriv->dm.is_any_nonbepkts = false;
	last_txok_cnt = rtlpriv->stats.txbytesunicast;
	last_rxok_cnt = rtlpriv->stats.rxbytesunicast;
}