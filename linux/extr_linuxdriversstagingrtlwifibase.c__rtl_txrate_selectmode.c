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
typedef  void* u8 ;
struct rtl_tcb_desc {int use_driver_rate; scalar_t__ mac_id; void* ratr_index; int /*<<< orphan*/  hw_rate; scalar_t__ broadcast; scalar_t__ multicast; int /*<<< orphan*/  disable_ratefallback; } ;
struct rtl_sta_info {int wireless_mode; void* ratr_index; } ;
struct TYPE_3__ {scalar_t__ useramask; } ;
struct rtl_priv {TYPE_2__* cfg; TYPE_1__ dm; } ;
struct rtl_mac {scalar_t__ opmode; int mode; } ;
struct ieee80211_sta {scalar_t__ aid; scalar_t__ drv_priv; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {int spec_ver; int /*<<< orphan*/ * maps; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 void* RATR_INX_WIRELESS_AC_24N ; 
 void* RATR_INX_WIRELESS_AC_5N ; 
 void* RATR_INX_WIRELESS_B ; 
 void* RATR_INX_WIRELESS_G ; 
 void* RATR_INX_WIRELESS_GB ; 
 void* RATR_INX_WIRELESS_MC ; 
 void* RATR_INX_WIRELESS_NG ; 
 void* RATR_INX_WIRELESS_NGB ; 
 size_t RTL_RC_CCK_RATE2M ; 
 int RTL_SPEC_NEW_RATEID ; 
 int WIRELESS_MODE_A ; 
 int WIRELESS_MODE_AC_24G ; 
 int WIRELESS_MODE_AC_5G ; 
 int WIRELESS_MODE_B ; 
 int WIRELESS_MODE_G ; 
 int WIRELESS_MODE_N_24G ; 
 int WIRELESS_MODE_N_5G ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 void* rtl_mrate_idx_to_arfr_id (struct ieee80211_hw*,void*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl_txrate_selectmode(struct ieee80211_hw *hw,
				   struct ieee80211_sta *sta,
				   struct rtl_tcb_desc *tcb_desc)
{
#define SET_RATE_ID(rate_id)					\
	((rtlpriv->cfg->spec_ver & RTL_SPEC_NEW_RATEID) ?	\
		rtl_mrate_idx_to_arfr_id(hw, rate_id,		\
			(sta_entry ? sta_entry->wireless_mode :	\
			 WIRELESS_MODE_G)) :			\
		rate_id)

	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_sta_info *sta_entry = NULL;
	u8 ratr_index = SET_RATE_ID(RATR_INX_WIRELESS_MC);

	if (sta) {
		sta_entry = (struct rtl_sta_info *)sta->drv_priv;
		ratr_index = sta_entry->ratr_index;
	}
	if (!tcb_desc->disable_ratefallback || !tcb_desc->use_driver_rate) {
		if (mac->opmode == NL80211_IFTYPE_STATION) {
			tcb_desc->ratr_index = 0;
		} else if (mac->opmode == NL80211_IFTYPE_ADHOC ||
				mac->opmode == NL80211_IFTYPE_MESH_POINT) {
			if (tcb_desc->multicast || tcb_desc->broadcast) {
				tcb_desc->hw_rate =
				    rtlpriv->cfg->maps[RTL_RC_CCK_RATE2M];
				tcb_desc->use_driver_rate = 1;
				tcb_desc->ratr_index =
					SET_RATE_ID(RATR_INX_WIRELESS_MC);
			} else {
				tcb_desc->ratr_index = ratr_index;
			}
		} else if (mac->opmode == NL80211_IFTYPE_AP) {
			tcb_desc->ratr_index = ratr_index;
		}
	}

	if (rtlpriv->dm.useramask) {
		tcb_desc->ratr_index = ratr_index;
		/* TODO we will differentiate adhoc and station future  */
		if (mac->opmode == NL80211_IFTYPE_STATION ||
		    mac->opmode == NL80211_IFTYPE_MESH_POINT) {
			tcb_desc->mac_id = 0;

			if (sta &&
			    (rtlpriv->cfg->spec_ver & RTL_SPEC_NEW_RATEID))
				;	/* use sta_entry->ratr_index */
			else if (mac->mode == WIRELESS_MODE_AC_5G)
				tcb_desc->ratr_index =
					SET_RATE_ID(RATR_INX_WIRELESS_AC_5N);
			else if (mac->mode == WIRELESS_MODE_AC_24G)
				tcb_desc->ratr_index =
					SET_RATE_ID(RATR_INX_WIRELESS_AC_24N);
			else if (mac->mode == WIRELESS_MODE_N_24G)
				tcb_desc->ratr_index =
					SET_RATE_ID(RATR_INX_WIRELESS_NGB);
			else if (mac->mode == WIRELESS_MODE_N_5G)
				tcb_desc->ratr_index =
					SET_RATE_ID(RATR_INX_WIRELESS_NG);
			else if (mac->mode & WIRELESS_MODE_G)
				tcb_desc->ratr_index =
					SET_RATE_ID(RATR_INX_WIRELESS_GB);
			else if (mac->mode & WIRELESS_MODE_B)
				tcb_desc->ratr_index =
					SET_RATE_ID(RATR_INX_WIRELESS_B);
			else if (mac->mode & WIRELESS_MODE_A)
				tcb_desc->ratr_index =
					SET_RATE_ID(RATR_INX_WIRELESS_G);

		} else if (mac->opmode == NL80211_IFTYPE_AP ||
			mac->opmode == NL80211_IFTYPE_ADHOC) {
			if (sta) {
				if (sta->aid > 0)
					tcb_desc->mac_id = sta->aid + 1;
				else
					tcb_desc->mac_id = 1;
			} else {
				tcb_desc->mac_id = 0;
			}
		}
	}
#undef SET_RATE_ID
}