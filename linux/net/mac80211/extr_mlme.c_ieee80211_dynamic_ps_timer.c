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
struct timer_list {int dummy; } ;
struct ieee80211_local {int /*<<< orphan*/  dynamic_ps_enable_work; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  dynamic_ps_timer ; 
 struct ieee80211_local* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ieee80211_local* local ; 

void ieee80211_dynamic_ps_timer(struct timer_list *t)
{
	struct ieee80211_local *local = from_timer(local, t, dynamic_ps_timer);

	ieee80211_queue_work(&local->hw, &local->dynamic_ps_enable_work);
}