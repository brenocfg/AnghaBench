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
struct task_struct {struct mempolicy* mempolicy; } ;
struct mempolicy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mpol_put (struct mempolicy*) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 

void mpol_put_task_policy(struct task_struct *task)
{
	struct mempolicy *pol;

	task_lock(task);
	pol = task->mempolicy;
	task->mempolicy = NULL;
	task_unlock(task);
	mpol_put(pol);
}