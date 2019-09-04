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
struct tid_ampdu_rx {int /*<<< orphan*/  tid; int /*<<< orphan*/  sta; } ;

/* Variables and functions */
 struct tid_ampdu_rx* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_release_reorder_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  reorder_timer ; 
 struct tid_ampdu_rx* tid_rx ; 

__attribute__((used)) static void sta_rx_agg_reorder_timer_expired(struct timer_list *t)
{
	struct tid_ampdu_rx *tid_rx = from_timer(tid_rx, t, reorder_timer);

	rcu_read_lock();
	ieee80211_release_reorder_timeout(tid_rx->sta, tid_rx->tid);
	rcu_read_unlock();
}