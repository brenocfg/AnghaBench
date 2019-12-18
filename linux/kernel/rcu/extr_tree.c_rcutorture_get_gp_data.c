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
typedef  enum rcutorture_type { ____Placeholder_rcutorture_type } rcutorture_type ;
struct TYPE_2__ {int /*<<< orphan*/  gp_seq; int /*<<< orphan*/  gp_flags; } ;

/* Variables and functions */
#define  RCU_FLAVOR 128 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned long rcu_seq_current (int /*<<< orphan*/ *) ; 
 TYPE_1__ rcu_state ; 

void rcutorture_get_gp_data(enum rcutorture_type test_type, int *flags,
			    unsigned long *gp_seq)
{
	switch (test_type) {
	case RCU_FLAVOR:
		*flags = READ_ONCE(rcu_state.gp_flags);
		*gp_seq = rcu_seq_current(&rcu_state.gp_seq);
		break;
	default:
		break;
	}
}