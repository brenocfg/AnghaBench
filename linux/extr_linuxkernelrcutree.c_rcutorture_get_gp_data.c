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
struct rcu_state {int /*<<< orphan*/  gp_seq; int /*<<< orphan*/  gp_flags; } ;
typedef  enum rcutorture_type { ____Placeholder_rcutorture_type } rcutorture_type ;

/* Variables and functions */
#define  RCU_BH_FLAVOR 130 
#define  RCU_FLAVOR 129 
#define  RCU_SCHED_FLAVOR 128 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 struct rcu_state rcu_bh_state ; 
 struct rcu_state rcu_sched_state ; 
 unsigned long rcu_seq_current (int /*<<< orphan*/ *) ; 
 struct rcu_state* rcu_state_p ; 

void rcutorture_get_gp_data(enum rcutorture_type test_type, int *flags,
			    unsigned long *gp_seq)
{
	struct rcu_state *rsp = NULL;

	switch (test_type) {
	case RCU_FLAVOR:
		rsp = rcu_state_p;
		break;
	case RCU_BH_FLAVOR:
		rsp = &rcu_bh_state;
		break;
	case RCU_SCHED_FLAVOR:
		rsp = &rcu_sched_state;
		break;
	default:
		break;
	}
	if (rsp == NULL)
		return;
	*flags = READ_ONCE(rsp->gp_flags);
	*gp_seq = rcu_seq_current(&rsp->gp_seq);
}