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
struct taprio_sched {int /*<<< orphan*/  current_entry_lock; int /*<<< orphan*/  admin_sched; int /*<<< orphan*/  oper_sched; } ;
struct sched_gate_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct sched_gate_list* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  switch_schedules (struct taprio_sched*,struct sched_gate_list**,struct sched_gate_list**) ; 

__attribute__((used)) static void taprio_offload_config_changed(struct taprio_sched *q)
{
	struct sched_gate_list *oper, *admin;

	spin_lock(&q->current_entry_lock);

	oper = rcu_dereference_protected(q->oper_sched,
					 lockdep_is_held(&q->current_entry_lock));
	admin = rcu_dereference_protected(q->admin_sched,
					  lockdep_is_held(&q->current_entry_lock));

	switch_schedules(q, &admin, &oper);

	spin_unlock(&q->current_entry_lock);
}