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
struct netns_ipvs {int /*<<< orphan*/  sync_buff_lock; } ;
struct ipvs_master_sync_state {struct ip_vs_sync_buff* sync_buff; } ;
struct ip_vs_sync_buff {scalar_t__ firstuse; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after_eq (scalar_t__,unsigned long) ; 

__attribute__((used)) static inline struct ip_vs_sync_buff *
get_curr_sync_buff(struct netns_ipvs *ipvs, struct ipvs_master_sync_state *ms,
		   unsigned long time)
{
	struct ip_vs_sync_buff *sb;

	spin_lock_bh(&ipvs->sync_buff_lock);
	sb = ms->sync_buff;
	if (sb && time_after_eq(jiffies - sb->firstuse, time)) {
		ms->sync_buff = NULL;
		__set_current_state(TASK_RUNNING);
	} else
		sb = NULL;
	spin_unlock_bh(&ipvs->sync_buff_lock);
	return sb;
}