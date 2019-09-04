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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 struct task_struct* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESRCH ; 
 struct task_struct* current ; 
 struct task_struct* find_task_by_vpid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static struct task_struct *
find_lively_task_by_vpid(pid_t vpid)
{
	struct task_struct *task;

	rcu_read_lock();
	if (!vpid)
		task = current;
	else
		task = find_task_by_vpid(vpid);
	if (task)
		get_task_struct(task);
	rcu_read_unlock();

	if (!task)
		return ERR_PTR(-ESRCH);

	return task;
}