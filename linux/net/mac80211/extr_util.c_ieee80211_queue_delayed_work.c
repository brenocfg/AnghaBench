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
struct ieee80211_local {int /*<<< orphan*/  workqueue; } ;
struct ieee80211_hw {int dummy; } ;
struct delayed_work {int dummy; } ;

/* Variables and functions */
 struct ieee80211_local* hw_to_local (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_can_queue_work (struct ieee80211_local*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,struct delayed_work*,unsigned long) ; 

void ieee80211_queue_delayed_work(struct ieee80211_hw *hw,
				  struct delayed_work *dwork,
				  unsigned long delay)
{
	struct ieee80211_local *local = hw_to_local(hw);

	if (!ieee80211_can_queue_work(local))
		return;

	queue_delayed_work(local->workqueue, dwork, delay);
}