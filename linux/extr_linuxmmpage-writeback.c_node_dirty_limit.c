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
struct task_struct {int flags; } ;
struct pglist_data {int dummy; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PF_LESS_THROTTLE ; 
 struct task_struct* current ; 
 unsigned long global_dirtyable_memory () ; 
 unsigned long node_dirtyable_memory (struct pglist_data*) ; 
 scalar_t__ rt_task (struct task_struct*) ; 
 scalar_t__ vm_dirty_bytes ; 
 unsigned long vm_dirty_ratio ; 

__attribute__((used)) static unsigned long node_dirty_limit(struct pglist_data *pgdat)
{
	unsigned long node_memory = node_dirtyable_memory(pgdat);
	struct task_struct *tsk = current;
	unsigned long dirty;

	if (vm_dirty_bytes)
		dirty = DIV_ROUND_UP(vm_dirty_bytes, PAGE_SIZE) *
			node_memory / global_dirtyable_memory();
	else
		dirty = vm_dirty_ratio * node_memory / 100;

	if (tsk->flags & PF_LESS_THROTTLE || rt_task(tsk))
		dirty += dirty / 4;

	return dirty;
}