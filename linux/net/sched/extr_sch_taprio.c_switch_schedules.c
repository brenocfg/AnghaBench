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
struct taprio_sched {int /*<<< orphan*/  admin_sched; int /*<<< orphan*/  oper_sched; } ;
struct sched_gate_list {int /*<<< orphan*/  rcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct sched_gate_list*) ; 
 int /*<<< orphan*/  taprio_free_sched_cb ; 

__attribute__((used)) static void switch_schedules(struct taprio_sched *q,
			     struct sched_gate_list **admin,
			     struct sched_gate_list **oper)
{
	rcu_assign_pointer(q->oper_sched, *admin);
	rcu_assign_pointer(q->admin_sched, NULL);

	if (*oper)
		call_rcu(&(*oper)->rcu, taprio_free_sched_cb);

	*oper = *admin;
	*admin = NULL;
}