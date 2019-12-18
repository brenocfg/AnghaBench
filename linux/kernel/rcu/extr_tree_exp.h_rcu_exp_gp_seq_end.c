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
struct TYPE_2__ {int /*<<< orphan*/  expedited_sequence; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_seq_end (int /*<<< orphan*/ *) ; 
 TYPE_1__ rcu_state ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static void rcu_exp_gp_seq_end(void)
{
	rcu_seq_end(&rcu_state.expedited_sequence);
	smp_mb(); /* Ensure that consecutive grace periods serialize. */
}