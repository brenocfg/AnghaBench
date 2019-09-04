#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rcu_dynticks {int /*<<< orphan*/  dynticks; } ;
struct TYPE_3__ {int /*<<< orphan*/  rcu_need_heavy_qs; } ;

/* Variables and functions */
 int RCU_DYNTICK_CTRL_CTR ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_cpu_write (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ rcu_dynticks ; 
 struct rcu_dynticks* this_cpu_ptr (TYPE_1__*) ; 

__attribute__((used)) static void rcu_momentary_dyntick_idle(void)
{
	struct rcu_dynticks *rdtp = this_cpu_ptr(&rcu_dynticks);
	int special;

	raw_cpu_write(rcu_dynticks.rcu_need_heavy_qs, false);
	special = atomic_add_return(2 * RCU_DYNTICK_CTRL_CTR, &rdtp->dynticks);
	/* It is illegal to call this from idle state. */
	WARN_ON_ONCE(!(special & RCU_DYNTICK_CTRL_CTR));
}