#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  chan; } ;
struct ieee80211_if_ibss {TYPE_4__ chandef; int /*<<< orphan*/  privacy; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  bssid; } ;
struct TYPE_5__ {struct ieee80211_if_ibss ibss; } ;
struct ieee80211_sub_if_data {TYPE_4__ csa_chandef; TYPE_3__* local; TYPE_1__ u; } ;
struct cfg80211_bss {int /*<<< orphan*/  channel; } ;
struct TYPE_6__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_7__ {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_BSS_TYPE_IBSS ; 
 int /*<<< orphan*/  IEEE80211_PRIVACY (int /*<<< orphan*/ ) ; 
 struct cfg80211_bss* cfg80211_get_bss (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_put_bss (int /*<<< orphan*/ ,struct cfg80211_bss*) ; 
 int ieee80211_ibss_csa_beacon (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdata_assert_lock (struct ieee80211_sub_if_data*) ; 

int ieee80211_ibss_finish_csa(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_if_ibss *ifibss = &sdata->u.ibss;
	struct cfg80211_bss *cbss;
	int err, changed = 0;

	sdata_assert_lock(sdata);

	/* update cfg80211 bss information with the new channel */
	if (!is_zero_ether_addr(ifibss->bssid)) {
		cbss = cfg80211_get_bss(sdata->local->hw.wiphy,
					ifibss->chandef.chan,
					ifibss->bssid, ifibss->ssid,
					ifibss->ssid_len,
					IEEE80211_BSS_TYPE_IBSS,
					IEEE80211_PRIVACY(ifibss->privacy));
		/* XXX: should not really modify cfg80211 data */
		if (cbss) {
			cbss->channel = sdata->csa_chandef.chan;
			cfg80211_put_bss(sdata->local->hw.wiphy, cbss);
		}
	}

	ifibss->chandef = sdata->csa_chandef;

	/* generate the beacon */
	err = ieee80211_ibss_csa_beacon(sdata, NULL);
	if (err < 0)
		return err;

	changed |= err;

	return changed;
}