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
struct cpuidle_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  idle_set_state (int /*<<< orphan*/ ,struct cpuidle_state*) ; 
 int /*<<< orphan*/  this_rq () ; 

void sched_idle_set_state(struct cpuidle_state *idle_state)
{
	idle_set_state(this_rq(), idle_state);
}