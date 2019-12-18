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
struct ieee80211_local {int /*<<< orphan*/  roc_work; int /*<<< orphan*/  workqueue; } ;

/* Variables and functions */
 long LONG_MAX ; 
 long ieee80211_end_finished_rocs (struct ieee80211_local*,unsigned long) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,long) ; 

__attribute__((used)) static bool ieee80211_recalc_sw_work(struct ieee80211_local *local,
				     unsigned long now)
{
	long dur = ieee80211_end_finished_rocs(local, now);

	if (dur == LONG_MAX)
		return false;

	mod_delayed_work(local->workqueue, &local->roc_work, dur);
	return true;
}