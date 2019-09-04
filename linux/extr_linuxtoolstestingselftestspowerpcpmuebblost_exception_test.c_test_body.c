#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int exclude_kernel; int exclude_hv; int exclude_idle; } ;
struct event {TYPE_1__ attr; } ;
struct TYPE_5__ {int ebb_count; } ;
struct TYPE_6__ {TYPE_2__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  SPRN_PMC4 ; 
 int /*<<< orphan*/  count_pmc (int,int) ; 
 int /*<<< orphan*/  dump_ebb_hw_state () ; 
 int /*<<< orphan*/  dump_summary_ebb_state () ; 
 int /*<<< orphan*/  ebb_check_count (int,int,int) ; 
 int /*<<< orphan*/  ebb_enable_pmc_counting (int) ; 
 int ebb_event_enable (struct event*) ; 
 int /*<<< orphan*/  ebb_freeze_pmcs () ; 
 int /*<<< orphan*/  ebb_global_disable () ; 
 int /*<<< orphan*/  ebb_global_enable () ; 
 int /*<<< orphan*/  ebb_is_supported () ; 
 TYPE_3__ ebb_state ; 
 int /*<<< orphan*/  event_close (struct event*) ; 
 int /*<<< orphan*/  event_init_named (struct event*,int,char*) ; 
 int /*<<< orphan*/  event_leader_ebb_init (struct event*) ; 
 int event_open (struct event*) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int pmc_sample_period (int) ; 
 int sample_period ; 
 int /*<<< orphan*/  sched_yield () ; 
 int /*<<< orphan*/  setup_ebb_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  standard_ebb_callee ; 

__attribute__((used)) static int test_body(void)
{
	int i, orig_period, max_period;
	struct event event;

	SKIP_IF(!ebb_is_supported());

	/* We use PMC4 to make sure the kernel switches all counters correctly */
	event_init_named(&event, 0x40002, "instructions");
	event_leader_ebb_init(&event);

	event.attr.exclude_kernel = 1;
	event.attr.exclude_hv = 1;
	event.attr.exclude_idle = 1;

	FAIL_IF(event_open(&event));

	ebb_enable_pmc_counting(4);
	setup_ebb_handler(standard_ebb_callee);
	ebb_global_enable();
	FAIL_IF(ebb_event_enable(&event));

	/*
	 * We want a low sample period, but we also want to get out of the EBB
	 * handler without tripping up again.
	 *
	 * This value picked after much experimentation.
	 */
	orig_period = max_period = sample_period = 400;

	mtspr(SPRN_PMC4, pmc_sample_period(sample_period));

	while (ebb_state.stats.ebb_count < 1000000) {
		/*
		 * We are trying to get the EBB exception to race exactly with
		 * us entering the kernel to do the syscall. We then need the
		 * kernel to decide our timeslice is up and context switch to
		 * the other thread. When we come back our EBB will have been
		 * lost and we'll spin in this while loop forever.
		 */

		for (i = 0; i < 100000; i++)
			sched_yield();

		/* Change the sample period slightly to try and hit the race */
		if (sample_period >= (orig_period + 200))
			sample_period = orig_period;
		else
			sample_period++;

		if (sample_period > max_period)
			max_period = sample_period;
	}

	ebb_freeze_pmcs();
	ebb_global_disable();

	count_pmc(4, sample_period);
	mtspr(SPRN_PMC4, 0xdead);

	dump_summary_ebb_state();
	dump_ebb_hw_state();

	event_close(&event);

	FAIL_IF(ebb_state.stats.ebb_count == 0);

	/* We vary our sample period so we need extra fudge here */
	FAIL_IF(!ebb_check_count(4, orig_period, 2 * (max_period - orig_period)));

	return 0;
}