#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tomoyo_task {int /*<<< orphan*/ * old_domain_info; TYPE_1__* domain_info; } ;
struct task_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct task_struct* current ; 
 struct tomoyo_task* tomoyo_task (struct task_struct*) ; 

__attribute__((used)) static int tomoyo_task_alloc(struct task_struct *task,
			     unsigned long clone_flags)
{
	struct tomoyo_task *old = tomoyo_task(current);
	struct tomoyo_task *new = tomoyo_task(task);

	new->domain_info = old->domain_info;
	atomic_inc(&new->domain_info->users);
	new->old_domain_info = NULL;
	return 0;
}