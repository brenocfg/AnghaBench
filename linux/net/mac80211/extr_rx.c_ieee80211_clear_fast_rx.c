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
struct sta_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  fast_rx; } ;
struct ieee80211_fast_rx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_rcu (struct ieee80211_fast_rx*,int /*<<< orphan*/ ) ; 
 struct ieee80211_fast_rx* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcu_head ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ieee80211_clear_fast_rx(struct sta_info *sta)
{
	struct ieee80211_fast_rx *old;

	spin_lock_bh(&sta->lock);
	old = rcu_dereference_protected(sta->fast_rx, true);
	RCU_INIT_POINTER(sta->fast_rx, NULL);
	spin_unlock_bh(&sta->lock);

	if (old)
		kfree_rcu(old, rcu_head);
}