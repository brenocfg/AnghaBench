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

/* Variables and functions */
 int /*<<< orphan*/  force_quiescent_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_state_p ; 

void rcu_force_quiescent_state(void)
{
	force_quiescent_state(rcu_state_p);
}