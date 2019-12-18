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

/* Variables and functions */
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct task_struct*,unsigned long) ; 
 int lsm_task_alloc (struct task_struct*) ; 
 int /*<<< orphan*/  security_task_free (struct task_struct*) ; 
 int /*<<< orphan*/  task_alloc ; 
 scalar_t__ unlikely (int) ; 

int security_task_alloc(struct task_struct *task, unsigned long clone_flags)
{
	int rc = lsm_task_alloc(task);

	if (rc)
		return rc;
	rc = call_int_hook(task_alloc, 0, task, clone_flags);
	if (unlikely(rc))
		security_task_free(task);
	return rc;
}