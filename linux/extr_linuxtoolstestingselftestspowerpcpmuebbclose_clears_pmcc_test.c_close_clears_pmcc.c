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
struct event {int dummy; } ;
struct TYPE_3__ {int ebb_count; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  SPRN_BESCR ; 
 int /*<<< orphan*/  SPRN_EBBHR ; 
 int /*<<< orphan*/  SPRN_EBBRR ; 
 int /*<<< orphan*/  SPRN_PMC1 ; 
 int catch_sigill (int /*<<< orphan*/ ) ; 
 int core_busy_loop () ; 
 int /*<<< orphan*/  ebb_enable_pmc_counting (int) ; 
 int ebb_event_enable (struct event*) ; 
 int /*<<< orphan*/  ebb_global_disable () ; 
 int /*<<< orphan*/  ebb_global_enable () ; 
 int /*<<< orphan*/  ebb_is_supported () ; 
 TYPE_2__ ebb_state ; 
 int /*<<< orphan*/  event_close (struct event*) ; 
 int /*<<< orphan*/  event_init_named (struct event*,int,char*) ; 
 int /*<<< orphan*/  event_leader_ebb_init (struct event*) ; 
 int event_open (struct event*) ; 
 int /*<<< orphan*/  mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmc_sample_period (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sample_period ; 
 int /*<<< orphan*/  setup_ebb_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  standard_ebb_callee ; 
 int /*<<< orphan*/  write_pmc1 ; 

int close_clears_pmcc(void)
{
	struct event event;

	SKIP_IF(!ebb_is_supported());

	event_init_named(&event, 0x1001e, "cycles");
	event_leader_ebb_init(&event);

	FAIL_IF(event_open(&event));

	ebb_enable_pmc_counting(1);
	setup_ebb_handler(standard_ebb_callee);
	ebb_global_enable();
	FAIL_IF(ebb_event_enable(&event));

	mtspr(SPRN_PMC1, pmc_sample_period(sample_period));

	while (ebb_state.stats.ebb_count < 1)
		FAIL_IF(core_busy_loop());

	ebb_global_disable();
	event_close(&event);

	FAIL_IF(ebb_state.stats.ebb_count == 0);

	/* The real test is here, do we take a SIGILL when writing PMU regs now
	 * that we have closed the event. We expect that we will. */

	FAIL_IF(catch_sigill(write_pmc1));

	/* We should still be able to read EBB regs though */
	mfspr(SPRN_EBBHR);
	mfspr(SPRN_EBBRR);
	mfspr(SPRN_BESCR);

	return 0;
}