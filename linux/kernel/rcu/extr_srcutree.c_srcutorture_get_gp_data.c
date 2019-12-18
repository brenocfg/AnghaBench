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
struct srcu_struct {int /*<<< orphan*/  srcu_gp_seq; } ;
typedef  enum rcutorture_type { ____Placeholder_rcutorture_type } rcutorture_type ;

/* Variables and functions */
 int SRCU_FLAVOR ; 
 unsigned long rcu_seq_current (int /*<<< orphan*/ *) ; 

void srcutorture_get_gp_data(enum rcutorture_type test_type,
			     struct srcu_struct *ssp, int *flags,
			     unsigned long *gp_seq)
{
	if (test_type != SRCU_FLAVOR)
		return;
	*flags = 0;
	*gp_seq = rcu_seq_current(&ssp->srcu_gp_seq);
}