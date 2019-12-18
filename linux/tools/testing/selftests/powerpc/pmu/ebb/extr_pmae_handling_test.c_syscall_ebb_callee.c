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
 int /*<<< orphan*/  SPRN_BESCR ; 
 int /*<<< orphan*/  SPRN_MMCR0 ; 
 scalar_t__ after ; 
 scalar_t__ before ; 
 int /*<<< orphan*/  count_pmc (int,int /*<<< orphan*/ ) ; 
 TYPE_2__ ebb_state ; 
 void* mfspr (int /*<<< orphan*/ ) ; 
 int mmcr0_mismatch ; 
 int /*<<< orphan*/  reset_ebb () ; 
 int /*<<< orphan*/  sample_period ; 
 int /*<<< orphan*/  sched_yield () ; 

__attribute__((used)) static void syscall_ebb_callee(void)
{
	uint64_t val;

	val = mfspr(SPRN_BESCR);
	if (!(val & BESCR_PMEO)) {
		ebb_state.stats.spurious++;
		goto out;
	}

	ebb_state.stats.ebb_count++;
	count_pmc(1, sample_period);

	before = mfspr(SPRN_MMCR0);

	/* Try and get ourselves scheduled, to force a PMU context switch */
	sched_yield();

	after = mfspr(SPRN_MMCR0);
	if (before != after)
		mmcr0_mismatch = true;

out:
	reset_ebb();
}