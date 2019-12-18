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
struct rcu_data {int /*<<< orphan*/  mynode; int /*<<< orphan*/  cpu; int /*<<< orphan*/  gp_seq; int /*<<< orphan*/  dynticks_snap; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPS (char*) ; 
 scalar_t__ rcu_dynticks_in_eqs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_dynticks_snap (struct rcu_data*) ; 
 int /*<<< orphan*/  rcu_gpnum_ovf (int /*<<< orphan*/ ,struct rcu_data*) ; 
 TYPE_1__ rcu_state ; 
 int /*<<< orphan*/  trace_rcu_fqs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dyntick_save_progress_counter(struct rcu_data *rdp)
{
	rdp->dynticks_snap = rcu_dynticks_snap(rdp);
	if (rcu_dynticks_in_eqs(rdp->dynticks_snap)) {
		trace_rcu_fqs(rcu_state.name, rdp->gp_seq, rdp->cpu, TPS("dti"));
		rcu_gpnum_ovf(rdp->mynode, rdp);
		return 1;
	}
	return 0;
}