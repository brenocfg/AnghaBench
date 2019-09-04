#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_3__ {int /*<<< orphan*/  no_overflow; int /*<<< orphan*/  ebb_count; int /*<<< orphan*/  spurious; } ;
struct TYPE_4__ {TYPE_1__ stats; scalar_t__* pmc_enable; int /*<<< orphan*/  trace; } ;

/* Variables and functions */
 int BESCR_PMEO ; 
 size_t PMC_INDEX (int) ; 
 int /*<<< orphan*/  SPRN_BESCR ; 
 int /*<<< orphan*/  SPRN_MMCR0 ; 
 scalar_t__ count_pmc (int,int /*<<< orphan*/ ) ; 
 TYPE_2__ ebb_state ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_ebb () ; 
 int /*<<< orphan*/  sample_period ; 
 int /*<<< orphan*/  trace_log_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_log_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void standard_ebb_callee(void)
{
	int found, i;
	u64 val;

	val = mfspr(SPRN_BESCR);
	if (!(val & BESCR_PMEO)) {
		ebb_state.stats.spurious++;
		goto out;
	}

	ebb_state.stats.ebb_count++;
	trace_log_counter(ebb_state.trace, ebb_state.stats.ebb_count);

	val = mfspr(SPRN_MMCR0);
	trace_log_reg(ebb_state.trace, SPRN_MMCR0, val);

	found = 0;
	for (i = 1; i <= 6; i++) {
		if (ebb_state.pmc_enable[PMC_INDEX(i)])
			found += count_pmc(i, sample_period);
	}

	if (!found)
		ebb_state.stats.no_overflow++;

out:
	reset_ebb();
}