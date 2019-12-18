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
struct net_device {int flags; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  mc; } ;
struct ieee80211_sub_if_data {int flags; struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  reconfig_filter; int /*<<< orphan*/  hw; int /*<<< orphan*/  filter_lock; int /*<<< orphan*/  mc_list; int /*<<< orphan*/  iff_allmultis; } ;

/* Variables and functions */
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int IEEE80211_SDATA_ALLMULTI ; 
 int IFF_ALLMULTI ; 
 int /*<<< orphan*/  __hw_addr_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ieee80211_set_multicast_list(struct net_device *dev)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	struct ieee80211_local *local = sdata->local;
	int allmulti, sdata_allmulti;

	allmulti = !!(dev->flags & IFF_ALLMULTI);
	sdata_allmulti = !!(sdata->flags & IEEE80211_SDATA_ALLMULTI);

	if (allmulti != sdata_allmulti) {
		if (dev->flags & IFF_ALLMULTI)
			atomic_inc(&local->iff_allmultis);
		else
			atomic_dec(&local->iff_allmultis);
		sdata->flags ^= IEEE80211_SDATA_ALLMULTI;
	}

	spin_lock_bh(&local->filter_lock);
	__hw_addr_sync(&local->mc_list, &dev->mc, dev->addr_len);
	spin_unlock_bh(&local->filter_lock);
	ieee80211_queue_work(&local->hw, &local->reconfig_filter);
}