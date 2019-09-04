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
struct rcu_state {int /*<<< orphan*/  gp_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_seq_current (int /*<<< orphan*/ *) ; 
 int rcu_seq_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rcu_gp_in_progress(struct rcu_state *rsp)
{
	return rcu_seq_state(rcu_seq_current(&rsp->gp_seq));
}