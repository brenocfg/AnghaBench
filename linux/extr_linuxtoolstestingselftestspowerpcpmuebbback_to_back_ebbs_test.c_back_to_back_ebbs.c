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
struct TYPE_5__ {scalar_t__ ebb_count; } ;
struct TYPE_6__ {TYPE_2__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int) ; 
 scalar_t__ NUMBER_OF_EBBS ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  SPRN_PMC1 ; 
 int core_busy_loop () ; 
 int /*<<< orphan*/  count_pmc (int,int) ; 
 int /*<<< orphan*/  dump_ebb_state () ; 
 int /*<<< orphan*/  ebb_callee ; 
 int ebb_event_enable (struct event*) ; 
 int /*<<< orphan*/  ebb_freeze_pmcs () ; 
 int /*<<< orphan*/  ebb_global_disable () ; 
 int /*<<< orphan*/  ebb_global_enable () ; 
 int /*<<< orphan*/  ebb_is_supported () ; 
 TYPE_3__ ebb_state ; 
 int /*<<< orphan*/  ebb_unfreeze_pmcs () ; 
 int /*<<< orphan*/  event_close (struct event*) ; 
 int /*<<< orphan*/  event_init_named (struct event*,int,char*) ; 
 int /*<<< orphan*/  event_leader_ebb_init (struct event*) ; 
 int event_open (struct event*) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmc_sample_period (int) ; 
 int sample_period ; 
 int /*<<< orphan*/  setup_ebb_handler (int /*<<< orphan*/ ) ; 

int back_to_back_ebbs(void)
{
	struct event event;

	SKIP_IF(!ebb_is_supported());

	event_init_named(&event, 0x1001e, "cycles");
	event_leader_ebb_init(&event);

	event.attr.exclude_kernel = 1;
	event.attr.exclude_hv = 1;
	event.attr.exclude_idle = 1;

	FAIL_IF(event_open(&event));

	setup_ebb_handler(ebb_callee);

	FAIL_IF(ebb_event_enable(&event));

	sample_period = 5;

	ebb_freeze_pmcs();
	mtspr(SPRN_PMC1, pmc_sample_period(sample_period));
	ebb_global_enable();
	ebb_unfreeze_pmcs();

	while (ebb_state.stats.ebb_count < NUMBER_OF_EBBS)
		FAIL_IF(core_busy_loop());

	ebb_global_disable();
	ebb_freeze_pmcs();

	count_pmc(1, sample_period);

	dump_ebb_state();

	event_close(&event);

	FAIL_IF(ebb_state.stats.ebb_count != NUMBER_OF_EBBS);

	return 0;
}