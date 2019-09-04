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
struct TYPE_2__ {unsigned long expedited_sequence; } ;

/* Variables and functions */
 TYPE_1__ rcu_sched_state ; 

unsigned long rcu_exp_batches_completed_sched(void)
{
	return rcu_sched_state.expedited_sequence;
}