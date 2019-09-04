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
struct ieee80211_vif {scalar_t__ type; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; } ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ath_softc {int /*<<< orphan*/  sc_ah; } ;
struct ath_common {int dummy; } ;
typedef  enum ieee80211_sta_state { ____Placeholder_ieee80211_sta_state } ieee80211_sta_state ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_CHANCTX_EVENT_AUTHORIZED ; 
 int /*<<< orphan*/  CONFIG ; 
 int IEEE80211_STA_ASSOC ; 
 int IEEE80211_STA_AUTHORIZED ; 
 int IEEE80211_STA_NONE ; 
 int IEEE80211_STA_NOTEXIST ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 scalar_t__ ath9k_is_chanctx_enabled () ; 
 int ath9k_sta_add (struct ieee80211_hw*,struct ieee80211_vif*,struct ieee80211_sta*) ; 
 int ath9k_sta_remove (struct ieee80211_hw*,struct ieee80211_vif*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  ath_chanctx_event (struct ath_softc*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath9k_sta_state(struct ieee80211_hw *hw,
			   struct ieee80211_vif *vif,
			   struct ieee80211_sta *sta,
			   enum ieee80211_sta_state old_state,
			   enum ieee80211_sta_state new_state)
{
	struct ath_softc *sc = hw->priv;
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	int ret = 0;

	if (old_state == IEEE80211_STA_NOTEXIST &&
	    new_state == IEEE80211_STA_NONE) {
		ret = ath9k_sta_add(hw, vif, sta);
		ath_dbg(common, CONFIG,
			"Add station: %pM\n", sta->addr);
	} else if (old_state == IEEE80211_STA_NONE &&
		   new_state == IEEE80211_STA_NOTEXIST) {
		ret = ath9k_sta_remove(hw, vif, sta);
		ath_dbg(common, CONFIG,
			"Remove station: %pM\n", sta->addr);
	}

	if (ath9k_is_chanctx_enabled()) {
		if (vif->type == NL80211_IFTYPE_STATION) {
			if (old_state == IEEE80211_STA_ASSOC &&
			    new_state == IEEE80211_STA_AUTHORIZED)
				ath_chanctx_event(sc, vif,
						  ATH_CHANCTX_EVENT_AUTHORIZED);
		}
	}

	return ret;
}