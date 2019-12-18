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
 int RCU_DYNTICK_CTRL_MASK ; 
 int atomic_add_return (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int rcu_dynticks_snap(struct rcu_data *rdp)
{
	int snap = atomic_add_return(0, &rdp->dynticks);

	return snap & ~RCU_DYNTICK_CTRL_MASK;
}