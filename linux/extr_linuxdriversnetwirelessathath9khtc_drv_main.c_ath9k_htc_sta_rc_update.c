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
typedef  int u32 ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_hw {int dummy; } ;
struct ath9k_htc_sta {int /*<<< orphan*/  rc_update_work; } ;

/* Variables and functions */
 int IEEE80211_RC_SUPP_RATES_CHANGED ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_htc_sta_rc_update(struct ieee80211_hw *hw,
				    struct ieee80211_vif *vif,
				    struct ieee80211_sta *sta, u32 changed)
{
	struct ath9k_htc_sta *ista = (struct ath9k_htc_sta *) sta->drv_priv;

	if (!(changed & IEEE80211_RC_SUPP_RATES_CHANGED))
		return;

	schedule_work(&ista->rc_update_work);
}