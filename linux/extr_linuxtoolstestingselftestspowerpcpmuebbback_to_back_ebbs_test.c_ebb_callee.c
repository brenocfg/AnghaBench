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
typedef  int uint64_t ;
struct TYPE_3__ {scalar_t__ ebb_count; int /*<<< orphan*/  spurious; } ;
struct TYPE_4__ {int /*<<< orphan*/  trace; TYPE_1__ stats; } ;

/* Variables and functions */
 int BESCR_PMEO ; 
 int /*<<< orphan*/  MMCR0_PMAO ; 
 scalar_t__ NUMBER_OF_EBBS ; 
 int /*<<< orphan*/  SPRN_BESCR ; 
 int /*<<< orphan*/  SPRN_MMCR0 ; 
 int /*<<< orphan*/  SPRN_PMC1 ; 
 int /*<<< orphan*/  SPRN_SIAR ; 
 int /*<<< orphan*/  count_pmc (int,int /*<<< orphan*/ ) ; 
 TYPE_2__ ebb_state ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_ebb () ; 
 int /*<<< orphan*/  reset_ebb_with_clear_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sample_period ; 
 int /*<<< orphan*/  trace_log_counter (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  trace_log_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ebb_callee(void)
{
	uint64_t siar, val;

	val = mfspr(SPRN_BESCR);
	if (!(val & BESCR_PMEO)) {
		ebb_state.stats.spurious++;
		goto out;
	}

	ebb_state.stats.ebb_count++;
	trace_log_counter(ebb_state.trace, ebb_state.stats.ebb_count);

	/* Resets the PMC */
	count_pmc(1, sample_period);

out:
	if (ebb_state.stats.ebb_count == NUMBER_OF_EBBS)
		/* Reset but leave counters frozen */
		reset_ebb_with_clear_mask(MMCR0_PMAO);
	else
		/* Unfreezes */
		reset_ebb();

	/* Do some stuff to chew some cycles and pop the counter */
	siar = mfspr(SPRN_SIAR);
	trace_log_reg(ebb_state.trace, SPRN_SIAR, siar);

	val = mfspr(SPRN_PMC1);
	trace_log_reg(ebb_state.trace, SPRN_PMC1, val);

	val = mfspr(SPRN_MMCR0);
	trace_log_reg(ebb_state.trace, SPRN_MMCR0, val);
}