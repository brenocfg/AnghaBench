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
struct srcu_struct {int /*<<< orphan*/  srcu_gp_seq_needed_exp; int /*<<< orphan*/  srcu_gp_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned long SRCU_INTERVAL ; 
 scalar_t__ ULONG_CMP_LT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long srcu_get_delay(struct srcu_struct *ssp)
{
	if (ULONG_CMP_LT(READ_ONCE(ssp->srcu_gp_seq),
			 READ_ONCE(ssp->srcu_gp_seq_needed_exp)))
		return 0;
	return SRCU_INTERVAL;
}