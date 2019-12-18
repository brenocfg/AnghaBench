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
typedef  size_t u8 ;
struct ieee80211_local {int /*<<< orphan*/ * active_txq_lock; int /*<<< orphan*/ * schedule_round; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct ieee80211_local* hw_to_local (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ieee80211_txq_schedule_start(struct ieee80211_hw *hw, u8 ac)
{
	struct ieee80211_local *local = hw_to_local(hw);

	spin_lock_bh(&local->active_txq_lock[ac]);
	local->schedule_round[ac]++;
	spin_unlock_bh(&local->active_txq_lock[ac]);
}