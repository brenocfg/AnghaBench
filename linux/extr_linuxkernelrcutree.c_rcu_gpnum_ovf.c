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
struct rcu_node {scalar_t__ gp_seq; } ;
struct rcu_data {scalar_t__ rcu_iw_gp_seq; int /*<<< orphan*/  gpwrap; int /*<<< orphan*/  gp_seq; } ;

/* Variables and functions */
 scalar_t__ ULONG_CMP_LT (scalar_t__,scalar_t__) ; 
 int ULONG_MAX ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raw_lockdep_assert_held_rcu_node (struct rcu_node*) ; 
 scalar_t__ rcu_seq_current (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rcu_gpnum_ovf(struct rcu_node *rnp, struct rcu_data *rdp)
{
	raw_lockdep_assert_held_rcu_node(rnp);
	if (ULONG_CMP_LT(rcu_seq_current(&rdp->gp_seq) + ULONG_MAX / 4,
			 rnp->gp_seq))
		WRITE_ONCE(rdp->gpwrap, true);
	if (ULONG_CMP_LT(rdp->rcu_iw_gp_seq + ULONG_MAX / 4, rnp->gp_seq))
		rdp->rcu_iw_gp_seq = rnp->gp_seq + ULONG_MAX / 4;
}