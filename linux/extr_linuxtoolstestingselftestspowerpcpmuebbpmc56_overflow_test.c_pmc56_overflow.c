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
 int /*<<< orphan*/  SPRN_PMC2 ; 
 int /*<<< orphan*/  SPRN_PMC5 ; 
 int /*<<< orphan*/  SPRN_PMC6 ; 
 int core_busy_loop () ; 
 int /*<<< orphan*/  count_pmc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_ebb_state () ; 
 int /*<<< orphan*/  ebb_callee ; 
 int ebb_event_enable (struct event*) ; 
 int /*<<< orphan*/  ebb_freeze_pmcs () ; 
 int /*<<< orphan*/  ebb_global_disable () ; 
 int /*<<< orphan*/  ebb_global_enable () ; 
 int /*<<< orphan*/  ebb_is_supported () ; 
 TYPE_3__ ebb_state ; 
 int /*<<< orphan*/  event_close (struct event*) ; 
 int /*<<< orphan*/  event_init (struct event*,int) ; 
 int /*<<< orphan*/  event_leader_ebb_init (struct event*) ; 
 int event_open (struct event*) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pmc56_overflowed ; 
 int /*<<< orphan*/  pmc_sample_period (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  sample_period ; 
 int /*<<< orphan*/  setup_ebb_handler (int /*<<< orphan*/ ) ; 

int pmc56_overflow(void)
{
	struct event event;

	SKIP_IF(!ebb_is_supported());

	/* Use PMC2 so we set PMCjCE, which enables PMC5/6 */
	event_init(&event, 0x2001e);
	event_leader_ebb_init(&event);

	event.attr.exclude_kernel = 1;
	event.attr.exclude_hv = 1;
	event.attr.exclude_idle = 1;

	FAIL_IF(event_open(&event));

	setup_ebb_handler(ebb_callee);
	ebb_global_enable();

	FAIL_IF(ebb_event_enable(&event));

	mtspr(SPRN_PMC2, pmc_sample_period(sample_period));
	mtspr(SPRN_PMC5, 0);
	mtspr(SPRN_PMC6, 0);

	while (ebb_state.stats.ebb_count < 10)
		FAIL_IF(core_busy_loop());

	ebb_global_disable();
	ebb_freeze_pmcs();

	count_pmc(2, sample_period);

	dump_ebb_state();

	printf("PMC5/6 overflow %d\n", pmc56_overflowed);

	event_close(&event);

	FAIL_IF(ebb_state.stats.ebb_count == 0 || pmc56_overflowed != 0);

	return 0;
}