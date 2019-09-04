#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_7__ {int num_non_be_pkt; } ;
struct TYPE_12__ {int is_any_nonbepkts; int is_cur_rdlstate; int current_turbo_edca; int /*<<< orphan*/  disable_framebursting; TYPE_1__ dbginfo; } ;
struct TYPE_9__ {scalar_t__ mode; } ;
struct TYPE_8__ {int txbytesunicast_inperiod; int rxbytesunicast_inperiod; } ;
struct rtl_priv {TYPE_6__ dm; int /*<<< orphan*/  hw; TYPE_5__* cfg; TYPE_3__ mac80211; TYPE_2__ stats; } ;
struct phy_dm_struct {int /*<<< orphan*/  is_linked; scalar_t__ wifi_test; scalar_t__ adapter; } ;
struct TYPE_11__ {TYPE_4__* ops; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* set_hw_reg ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AC0_BE ; 
 int /*<<< orphan*/  HW_VAR_AC_PARAM ; 
 int /*<<< orphan*/  REG_EDCA_BE_PARAM_8822B ; 
 scalar_t__ WIRELESS_MODE_B ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void odm_edca_turbo_check_ce(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct rtl_priv *rtlpriv = (struct rtl_priv *)dm->adapter;
	u64 cur_txok_cnt = 0;
	u64 cur_rxok_cnt = 0;
	u32 edca_be_ul = 0x5ea42b;
	u32 edca_be_dl = 0x5ea42b;
	u32 edca_be = 0x5ea42b;
	bool is_cur_rdlstate;
	bool edca_turbo_on = false;

	if (dm->wifi_test)
		return;

	if (!dm->is_linked) {
		rtlpriv->dm.is_any_nonbepkts = false;
		return;
	}

	if (rtlpriv->dm.dbginfo.num_non_be_pkt > 0x100)
		rtlpriv->dm.is_any_nonbepkts = true;
	rtlpriv->dm.dbginfo.num_non_be_pkt = 0;

	cur_txok_cnt = rtlpriv->stats.txbytesunicast_inperiod;
	cur_rxok_cnt = rtlpriv->stats.rxbytesunicast_inperiod;

	/*b_bias_on_rx = false;*/
	edca_turbo_on = ((!rtlpriv->dm.is_any_nonbepkts) &&
			 (!rtlpriv->dm.disable_framebursting)) ?
				true :
				false;

	if (rtlpriv->mac80211.mode == WIRELESS_MODE_B)
		goto label_exit;

	if (edca_turbo_on) {
		is_cur_rdlstate =
			(cur_rxok_cnt > cur_txok_cnt * 4) ? true : false;

		edca_be = is_cur_rdlstate ? edca_be_dl : edca_be_ul;
		rtl_write_dword(rtlpriv, REG_EDCA_BE_PARAM_8822B, edca_be);
		rtlpriv->dm.is_cur_rdlstate = is_cur_rdlstate;
		rtlpriv->dm.current_turbo_edca = true;
	} else {
		if (rtlpriv->dm.current_turbo_edca) {
			u8 tmp = AC0_BE;

			rtlpriv->cfg->ops->set_hw_reg(rtlpriv->hw,
						      HW_VAR_AC_PARAM,
						      (u8 *)(&tmp));
			rtlpriv->dm.current_turbo_edca = false;
		}
	}

label_exit:
	rtlpriv->dm.is_any_nonbepkts = false;
}