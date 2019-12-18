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
struct rcu_data {int /*<<< orphan*/  dynticks; } ;

/* Variables and functions */
 int RCU_DYNTICK_CTRL_CTR ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_data ; 
 struct rcu_data* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rcu_dynticks_eqs_online(void)
{
	struct rcu_data *rdp = this_cpu_ptr(&rcu_data);

	if (atomic_read(&rdp->dynticks) & RCU_DYNTICK_CTRL_CTR)
		return;
	atomic_add(RCU_DYNTICK_CTRL_CTR, &rdp->dynticks);
}