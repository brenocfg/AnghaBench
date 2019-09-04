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
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
struct sta_info {int /*<<< orphan*/  addr; TYPE_3__ sta; struct ieee80211_sub_if_data* sdata; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct ieee80211_sub_if_data {TYPE_2__* local; TYPE_1__ vif; } ;
struct TYPE_5__ {int /*<<< orphan*/  hw; int /*<<< orphan*/  sta_mtx; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENETDOWN ; 
 int ENOTUNIQ ; 
 int /*<<< orphan*/  NEEDS_UNIQUE_STA_ADDR ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_find_sta_by_ifaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ieee80211_hw_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_sdata_running (struct ieee80211_sub_if_data*) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int sta_info_insert_check(struct sta_info *sta)
{
	struct ieee80211_sub_if_data *sdata = sta->sdata;

	/*
	 * Can't be a WARN_ON because it can be triggered through a race:
	 * something inserts a STA (on one CPU) without holding the RTNL
	 * and another CPU turns off the net device.
	 */
	if (unlikely(!ieee80211_sdata_running(sdata)))
		return -ENETDOWN;

	if (WARN_ON(ether_addr_equal(sta->sta.addr, sdata->vif.addr) ||
		    is_multicast_ether_addr(sta->sta.addr)))
		return -EINVAL;

	/* The RCU read lock is required by rhashtable due to
	 * asynchronous resize/rehash.  We also require the mutex
	 * for correctness.
	 */
	rcu_read_lock();
	lockdep_assert_held(&sdata->local->sta_mtx);
	if (ieee80211_hw_check(&sdata->local->hw, NEEDS_UNIQUE_STA_ADDR) &&
	    ieee80211_find_sta_by_ifaddr(&sdata->local->hw, sta->addr, NULL)) {
		rcu_read_unlock();
		return -ENOTUNIQ;
	}
	rcu_read_unlock();

	return 0;
}