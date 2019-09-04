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
struct TYPE_3__ {int /*<<< orphan*/  ebb_count; int /*<<< orphan*/  spurious; } ;
struct TYPE_4__ {int /*<<< orphan*/  trace; TYPE_1__ stats; } ;

/* Variables and functions */
 int BESCR_PMEO ; 
 int MMCR0_FC ; 
 int MMCR0_PMAO ; 
 int /*<<< orphan*/  SPRN_BESCR ; 
 int /*<<< orphan*/  SPRN_MMCR0 ; 
 int /*<<< orphan*/  count_pmc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ counters_frozen ; 
 TYPE_2__ ebb_state ; 
 int /*<<< orphan*/  ebbs_while_frozen ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_ebb_with_clear_mask (int) ; 
 int /*<<< orphan*/  sample_period ; 
 int /*<<< orphan*/  trace_log_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_log_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_log_string (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ebb_callee(void)
{
	uint64_t mask, val;

	mask = MMCR0_PMAO | MMCR0_FC;

	val = mfspr(SPRN_BESCR);
	if (!(val & BESCR_PMEO)) {
		ebb_state.stats.spurious++;
		goto out;
	}

	ebb_state.stats.ebb_count++;
	trace_log_counter(ebb_state.trace, ebb_state.stats.ebb_count);

	val = mfspr(SPRN_MMCR0);
	trace_log_reg(ebb_state.trace, SPRN_MMCR0, val);

	if (counters_frozen) {
		trace_log_string(ebb_state.trace, "frozen");
		ebbs_while_frozen++;
		mask &= ~MMCR0_FC;
	}

	count_pmc(1, sample_period);
out:
	reset_ebb_with_clear_mask(mask);
}