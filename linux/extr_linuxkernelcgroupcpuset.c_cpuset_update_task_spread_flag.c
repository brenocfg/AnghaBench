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
struct task_struct {int dummy; } ;
struct cpuset {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_spread_page (struct cpuset*) ; 
 scalar_t__ is_spread_slab (struct cpuset*) ; 
 int /*<<< orphan*/  task_clear_spread_page (struct task_struct*) ; 
 int /*<<< orphan*/  task_clear_spread_slab (struct task_struct*) ; 
 int /*<<< orphan*/  task_set_spread_page (struct task_struct*) ; 
 int /*<<< orphan*/  task_set_spread_slab (struct task_struct*) ; 

__attribute__((used)) static void cpuset_update_task_spread_flag(struct cpuset *cs,
					struct task_struct *tsk)
{
	if (is_spread_page(cs))
		task_set_spread_page(tsk);
	else
		task_clear_spread_page(tsk);

	if (is_spread_slab(cs))
		task_set_spread_slab(tsk);
	else
		task_clear_spread_slab(tsk);
}