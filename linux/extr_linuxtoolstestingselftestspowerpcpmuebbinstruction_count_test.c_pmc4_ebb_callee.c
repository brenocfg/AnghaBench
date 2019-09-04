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
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int BESCR_PMEO ; 
 int /*<<< orphan*/  MMCR0_PMAO ; 
 int /*<<< orphan*/  SPRN_BESCR ; 
 int /*<<< orphan*/  count_pmc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ counters_frozen ; 
 TYPE_2__ ebb_state ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_ebb () ; 
 int /*<<< orphan*/  reset_ebb_with_clear_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sample_period ; 

__attribute__((used)) static void pmc4_ebb_callee(void)
{
	uint64_t val;

	val = mfspr(SPRN_BESCR);
	if (!(val & BESCR_PMEO)) {
		ebb_state.stats.spurious++;
		goto out;
	}

	ebb_state.stats.ebb_count++;
	count_pmc(4, sample_period);
out:
	if (counters_frozen)
		reset_ebb_with_clear_mask(MMCR0_PMAO);
	else
		reset_ebb();
}