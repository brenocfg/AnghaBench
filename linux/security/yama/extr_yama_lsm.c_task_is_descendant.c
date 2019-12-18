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
struct task_struct {scalar_t__ pid; int /*<<< orphan*/  real_parent; int /*<<< orphan*/  group_leader; } ;

/* Variables and functions */
 struct task_struct* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  thread_group_leader (struct task_struct*) ; 

__attribute__((used)) static int task_is_descendant(struct task_struct *parent,
			      struct task_struct *child)
{
	int rc = 0;
	struct task_struct *walker = child;

	if (!parent || !child)
		return 0;

	rcu_read_lock();
	if (!thread_group_leader(parent))
		parent = rcu_dereference(parent->group_leader);
	while (walker->pid > 0) {
		if (!thread_group_leader(walker))
			walker = rcu_dereference(walker->group_leader);
		if (walker == parent) {
			rc = 1;
			break;
		}
		walker = rcu_dereference(walker->real_parent);
	}
	rcu_read_unlock();

	return rc;
}