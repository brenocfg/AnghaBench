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
struct mem_cgroup {scalar_t__ under_oom; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_NORMAL ; 
 int /*<<< orphan*/  __wake_up (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mem_cgroup*) ; 
 int /*<<< orphan*/  memcg_oom_waitq ; 

__attribute__((used)) static void memcg_oom_recover(struct mem_cgroup *memcg)
{
	/*
	 * For the following lockless ->under_oom test, the only required
	 * guarantee is that it must see the state asserted by an OOM when
	 * this function is called as a result of userland actions
	 * triggered by the notification of the OOM.  This is trivially
	 * achieved by invoking mem_cgroup_mark_under_oom() before
	 * triggering notification.
	 */
	if (memcg && memcg->under_oom)
		__wake_up(&memcg_oom_waitq, TASK_NORMAL, 0, memcg);
}