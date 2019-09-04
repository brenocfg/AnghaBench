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
 int PER_RCU_NODE_PERIOD ; 
 int rcu_num_nodes ; 
 int rcu_seq_ctr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 

__attribute__((used)) static void rcu_gp_slow(struct rcu_state *rsp, int delay)
{
	if (delay > 0 &&
	    !(rcu_seq_ctr(rsp->gp_seq) %
	      (rcu_num_nodes * PER_RCU_NODE_PERIOD * delay)))
		schedule_timeout_uninterruptible(delay);
}