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
struct shuffle_task {int /*<<< orphan*/  st_l; struct task_struct* st_t; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 struct shuffle_task* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shuffle_task_list ; 
 int /*<<< orphan*/  shuffle_task_mutex ; 

void torture_shuffle_task_register(struct task_struct *tp)
{
	struct shuffle_task *stp;

	if (WARN_ON_ONCE(tp == NULL))
		return;
	stp = kmalloc(sizeof(*stp), GFP_KERNEL);
	if (WARN_ON_ONCE(stp == NULL))
		return;
	stp->st_t = tp;
	mutex_lock(&shuffle_task_mutex);
	list_add(&stp->st_l, &shuffle_task_list);
	mutex_unlock(&shuffle_task_mutex);
}