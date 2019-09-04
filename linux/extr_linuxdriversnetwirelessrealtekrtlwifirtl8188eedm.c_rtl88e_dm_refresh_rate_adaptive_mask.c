#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {long undec_sm_pwdb; int /*<<< orphan*/  useramask; } ;
struct rate_adaptive {int pre_ratr_state; int ratr_state; } ;
struct rtl_priv {TYPE_3__* cfg; TYPE_1__ dm; struct rate_adaptive ra; } ;
struct rtl_mac {scalar_t__ link_state; scalar_t__ opmode; int /*<<< orphan*/  bssid; } ;
struct rtl_hal {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* update_rate_tbl ) (struct ieee80211_hw*,struct ieee80211_sta*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_RATE ; 
 int /*<<< orphan*/  DBG_LOUD ; 
#define  DM_RATR_STA_HIGH 130 
#define  DM_RATR_STA_LOW 129 
#define  DM_RATR_STA_MIDDLE 128 
 scalar_t__ MAC80211_LINKED ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ is_hal_stop (struct rtl_hal*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct ieee80211_sta* rtl_find_sta (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,struct ieee80211_sta*,int,int) ; 

__attribute__((used)) static void rtl88e_dm_refresh_rate_adaptive_mask(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rate_adaptive *p_ra = &rtlpriv->ra;
	u32 low_rssithresh_for_ra, high_rssithresh_for_ra;
	struct ieee80211_sta *sta = NULL;

	if (is_hal_stop(rtlhal)) {
		RT_TRACE(rtlpriv, COMP_RATE, DBG_LOUD,
			 "driver is going to unload\n");
		return;
	}

	if (!rtlpriv->dm.useramask) {
		RT_TRACE(rtlpriv, COMP_RATE, DBG_LOUD,
			 "driver does not control rate adaptive mask\n");
		return;
	}

	if (mac->link_state == MAC80211_LINKED &&
	    mac->opmode == NL80211_IFTYPE_STATION) {
		switch (p_ra->pre_ratr_state) {
		case DM_RATR_STA_HIGH:
			high_rssithresh_for_ra = 50;
			low_rssithresh_for_ra = 20;
			break;
		case DM_RATR_STA_MIDDLE:
			high_rssithresh_for_ra = 55;
			low_rssithresh_for_ra = 20;
			break;
		case DM_RATR_STA_LOW:
			high_rssithresh_for_ra = 50;
			low_rssithresh_for_ra = 25;
			break;
		default:
			high_rssithresh_for_ra = 50;
			low_rssithresh_for_ra = 20;
			break;
		}

		if (rtlpriv->dm.undec_sm_pwdb >
		    (long)high_rssithresh_for_ra)
			p_ra->ratr_state = DM_RATR_STA_HIGH;
		else if (rtlpriv->dm.undec_sm_pwdb >
			 (long)low_rssithresh_for_ra)
			p_ra->ratr_state = DM_RATR_STA_MIDDLE;
		else
			p_ra->ratr_state = DM_RATR_STA_LOW;

		if (p_ra->pre_ratr_state != p_ra->ratr_state) {
			RT_TRACE(rtlpriv, COMP_RATE, DBG_LOUD,
				 "RSSI = %ld\n",
				  rtlpriv->dm.undec_sm_pwdb);
			RT_TRACE(rtlpriv, COMP_RATE, DBG_LOUD,
				 "RSSI_LEVEL = %d\n", p_ra->ratr_state);
			RT_TRACE(rtlpriv, COMP_RATE, DBG_LOUD,
				 "PreState = %d, CurState = %d\n",
				  p_ra->pre_ratr_state, p_ra->ratr_state);

			rcu_read_lock();
			sta = rtl_find_sta(hw, mac->bssid);
			if (sta)
				rtlpriv->cfg->ops->update_rate_tbl(hw, sta,
							p_ra->ratr_state,
								   true);
			rcu_read_unlock();

			p_ra->pre_ratr_state = p_ra->ratr_state;
		}
	}
}