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
struct pt_regs {int dummy; } ;
struct cpuacct {int /*<<< orphan*/  cpuusage; } ;
struct TYPE_2__ {int /*<<< orphan*/ * usages; } ;

/* Variables and functions */
 int CPUACCT_STAT_SYSTEM ; 
 int CPUACCT_STAT_USER ; 
 struct cpuacct* parent_ca (struct cpuacct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct cpuacct* task_ca (struct task_struct*) ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 
 TYPE_1__* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

void cpuacct_charge(struct task_struct *tsk, u64 cputime)
{
	struct cpuacct *ca;
	int index = CPUACCT_STAT_SYSTEM;
	struct pt_regs *regs = task_pt_regs(tsk);

	if (regs && user_mode(regs))
		index = CPUACCT_STAT_USER;

	rcu_read_lock();

	for (ca = task_ca(tsk); ca; ca = parent_ca(ca))
		this_cpu_ptr(ca->cpuusage)->usages[index] += cputime;

	rcu_read_unlock();
}