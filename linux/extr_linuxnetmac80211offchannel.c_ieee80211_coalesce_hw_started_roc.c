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
struct ieee80211_roc_work {int hw_begun; scalar_t__ duration; unsigned long start_time; int /*<<< orphan*/  list; int /*<<< orphan*/  started; } ;
struct ieee80211_local {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ieee80211_handle_roc_started (struct ieee80211_roc_work*,unsigned long) ; 
 unsigned long jiffies ; 
 scalar_t__ jiffies_to_msecs (unsigned long) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned long msecs_to_jiffies (scalar_t__) ; 

__attribute__((used)) static bool
ieee80211_coalesce_hw_started_roc(struct ieee80211_local *local,
				  struct ieee80211_roc_work *new_roc,
				  struct ieee80211_roc_work *cur_roc)
{
	unsigned long now = jiffies;
	unsigned long remaining;

	if (WARN_ON(!cur_roc->started))
		return false;

	/* if it was scheduled in the hardware, but not started yet,
	 * we can only combine if the older one had a longer duration
	 */
	if (!cur_roc->hw_begun && new_roc->duration > cur_roc->duration)
		return false;

	remaining = cur_roc->start_time +
		    msecs_to_jiffies(cur_roc->duration) -
		    now;

	/* if it doesn't fit entirely, schedule a new one */
	if (new_roc->duration > jiffies_to_msecs(remaining))
		return false;

	/* add just after the current one so we combine their finish later */
	list_add(&new_roc->list, &cur_roc->list);

	/* if the existing one has already begun then let this one also
	 * begin, otherwise they'll both be marked properly by the work
	 * struct that runs once the driver notifies us of the beginning
	 */
	if (cur_roc->hw_begun) {
		new_roc->hw_begun = true;
		ieee80211_handle_roc_started(new_roc, now);
	}

	return true;
}