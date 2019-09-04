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
struct TYPE_4__ {int flags; } ;
struct il_priv {TYPE_2__ staging; } ;
struct TYPE_3__ {scalar_t__ use_short_slot; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int NL80211_BAND_5GHZ ; 
 int RXON_FLG_AUTO_DETECT_MSK ; 
 int RXON_FLG_BAND_24G_MSK ; 
 int RXON_FLG_CCK_MSK ; 
 int RXON_FLG_SHORT_SLOT_MSK ; 

void
il_set_flags_for_band(struct il_priv *il, enum nl80211_band band,
		      struct ieee80211_vif *vif)
{
	if (band == NL80211_BAND_5GHZ) {
		il->staging.flags &=
		    ~(RXON_FLG_BAND_24G_MSK | RXON_FLG_AUTO_DETECT_MSK |
		      RXON_FLG_CCK_MSK);
		il->staging.flags |= RXON_FLG_SHORT_SLOT_MSK;
	} else {
		/* Copied from il_post_associate() */
		if (vif && vif->bss_conf.use_short_slot)
			il->staging.flags |= RXON_FLG_SHORT_SLOT_MSK;
		else
			il->staging.flags &= ~RXON_FLG_SHORT_SLOT_MSK;

		il->staging.flags |= RXON_FLG_BAND_24G_MSK;
		il->staging.flags |= RXON_FLG_AUTO_DETECT_MSK;
		il->staging.flags &= ~RXON_FLG_CCK_MSK;
	}
}