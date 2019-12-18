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
typedef  scalar_t__ u64 ;
struct task_struct {int dummy; } ;
struct cpuacct {int /*<<< orphan*/  cpustat; } ;
struct TYPE_2__ {int /*<<< orphan*/ * cpustat; } ;

/* Variables and functions */
 struct cpuacct* parent_ca (struct cpuacct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct cpuacct root_cpuacct ; 
 struct cpuacct* task_ca (struct task_struct*) ; 
 TYPE_1__* this_cpu_ptr (int /*<<< orphan*/ ) ; 

void cpuacct_account_field(struct task_struct *tsk, int index, u64 val)
{
	struct cpuacct *ca;

	rcu_read_lock();
	for (ca = task_ca(tsk); ca != &root_cpuacct; ca = parent_ca(ca))
		this_cpu_ptr(ca->cpustat)->cpustat[index] += val;
	rcu_read_unlock();
}