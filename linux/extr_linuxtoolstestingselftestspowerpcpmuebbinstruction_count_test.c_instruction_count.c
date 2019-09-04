#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int exclude_kernel; int exclude_hv; int exclude_idle; } ;
struct event {TYPE_1__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_OVERFLOW ; 
 int /*<<< orphan*/  FAIL_IF (int /*<<< orphan*/ ) ; 
 int MMCR0_FC ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  SPRN_MMCR0 ; 
 int /*<<< orphan*/  determine_overhead (struct event*) ; 
 int /*<<< orphan*/  do_count_loop (struct event*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ebb_event_enable (struct event*) ; 
 int /*<<< orphan*/  ebb_global_disable () ; 
 int /*<<< orphan*/  ebb_global_enable () ; 
 int /*<<< orphan*/  ebb_is_supported () ; 
 int /*<<< orphan*/  event_close (struct event*) ; 
 int /*<<< orphan*/  event_init_named (struct event*,int,char*) ; 
 int /*<<< orphan*/  event_leader_ebb_init (struct event*) ; 
 int /*<<< orphan*/  event_open (struct event*) ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmc4_ebb_callee ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sample_period ; 
 int /*<<< orphan*/  setup_ebb_handler (int /*<<< orphan*/ ) ; 

int instruction_count(void)
{
	struct event event;
	uint64_t overhead;

	SKIP_IF(!ebb_is_supported());

	event_init_named(&event, 0x400FA, "PM_RUN_INST_CMPL");
	event_leader_ebb_init(&event);
	event.attr.exclude_kernel = 1;
	event.attr.exclude_hv = 1;
	event.attr.exclude_idle = 1;

	FAIL_IF(event_open(&event));
	FAIL_IF(ebb_event_enable(&event));

	sample_period = COUNTER_OVERFLOW;

	setup_ebb_handler(pmc4_ebb_callee);
	mtspr(SPRN_MMCR0, mfspr(SPRN_MMCR0) & ~MMCR0_FC);
	ebb_global_enable();

	overhead = determine_overhead(&event);
	printf("Overhead of null loop: %lu instructions\n", overhead);

	/* Run for 1M instructions */
	FAIL_IF(do_count_loop(&event, 0x100000, overhead, true));

	/* Run for 10M instructions */
	FAIL_IF(do_count_loop(&event, 0xa00000, overhead, true));

	/* Run for 100M instructions */
	FAIL_IF(do_count_loop(&event, 0x6400000, overhead, true));

	/* Run for 1G instructions */
	FAIL_IF(do_count_loop(&event, 0x40000000, overhead, true));

	/* Run for 16G instructions */
	FAIL_IF(do_count_loop(&event, 0x400000000, overhead, true));

	/* Run for 64G instructions */
	FAIL_IF(do_count_loop(&event, 0x1000000000, overhead, true));

	/* Run for 128G instructions */
	FAIL_IF(do_count_loop(&event, 0x2000000000, overhead, true));

	ebb_global_disable();
	event_close(&event);

	printf("Finished OK\n");

	return 0;
}