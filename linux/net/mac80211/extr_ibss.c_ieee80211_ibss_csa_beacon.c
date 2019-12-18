#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_12__ {int /*<<< orphan*/  basic_rates; int /*<<< orphan*/  beacon_int; } ;
struct TYPE_13__ {TYPE_5__ bss_conf; } ;
struct TYPE_11__ {int /*<<< orphan*/  mtx; } ;
struct TYPE_14__ {int /*<<< orphan*/  chan; } ;
struct ieee80211_if_ibss {int /*<<< orphan*/  presp; TYPE_7__ chandef; scalar_t__ privacy; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  bssid; } ;
struct TYPE_8__ {struct ieee80211_if_ibss ibss; } ;
struct ieee80211_sub_if_data {TYPE_6__ vif; TYPE_4__ wdev; TYPE_3__* local; TYPE_1__ u; } ;
struct cfg80211_csa_settings {int dummy; } ;
struct cfg80211_bss_ies {int /*<<< orphan*/  tsf; } ;
struct cfg80211_bss {int /*<<< orphan*/  ies; } ;
struct beacon_data {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_10__ {TYPE_2__ hw; } ;

/* Variables and functions */
 int BSS_CHANGED_BEACON ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IEEE80211_BSS_TYPE_IBSS ; 
 int /*<<< orphan*/  IEEE80211_PRIVACY (scalar_t__) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WLAN_CAPABILITY_IBSS ; 
 int /*<<< orphan*/  WLAN_CAPABILITY_PRIVACY ; 
 struct cfg80211_bss* cfg80211_get_bss (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_put_bss (int /*<<< orphan*/ ,struct cfg80211_bss*) ; 
 struct beacon_data* ieee80211_ibss_build_presp (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ *,struct cfg80211_csa_settings*) ; 
 int /*<<< orphan*/  kfree_rcu (struct beacon_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct beacon_data*) ; 
 struct cfg80211_bss_ies* rcu_dereference (int /*<<< orphan*/ ) ; 
 struct beacon_data* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_head ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sdata_assert_lock (struct ieee80211_sub_if_data*) ; 

int ieee80211_ibss_csa_beacon(struct ieee80211_sub_if_data *sdata,
			      struct cfg80211_csa_settings *csa_settings)
{
	struct ieee80211_if_ibss *ifibss = &sdata->u.ibss;
	struct beacon_data *presp, *old_presp;
	struct cfg80211_bss *cbss;
	const struct cfg80211_bss_ies *ies;
	u16 capability = WLAN_CAPABILITY_IBSS;
	u64 tsf;
	int ret = 0;

	sdata_assert_lock(sdata);

	if (ifibss->privacy)
		capability |= WLAN_CAPABILITY_PRIVACY;

	cbss = cfg80211_get_bss(sdata->local->hw.wiphy, ifibss->chandef.chan,
				ifibss->bssid, ifibss->ssid,
				ifibss->ssid_len, IEEE80211_BSS_TYPE_IBSS,
				IEEE80211_PRIVACY(ifibss->privacy));

	if (WARN_ON(!cbss)) {
		ret = -EINVAL;
		goto out;
	}

	rcu_read_lock();
	ies = rcu_dereference(cbss->ies);
	tsf = ies->tsf;
	rcu_read_unlock();
	cfg80211_put_bss(sdata->local->hw.wiphy, cbss);

	old_presp = rcu_dereference_protected(ifibss->presp,
					  lockdep_is_held(&sdata->wdev.mtx));

	presp = ieee80211_ibss_build_presp(sdata,
					   sdata->vif.bss_conf.beacon_int,
					   sdata->vif.bss_conf.basic_rates,
					   capability, tsf, &ifibss->chandef,
					   NULL, csa_settings);
	if (!presp) {
		ret = -ENOMEM;
		goto out;
	}

	rcu_assign_pointer(ifibss->presp, presp);
	if (old_presp)
		kfree_rcu(old_presp, rcu_head);

	return BSS_CHANGED_BEACON;
 out:
	return ret;
}