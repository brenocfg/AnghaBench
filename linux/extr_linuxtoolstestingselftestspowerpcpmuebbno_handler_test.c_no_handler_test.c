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
typedef  int u64 ;
struct TYPE_2__ {int exclude_kernel; int exclude_hv; int exclude_idle; } ;
struct event {TYPE_1__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  SPRN_EBBHR ; 
 int /*<<< orphan*/  SPRN_MMCR0 ; 
 int /*<<< orphan*/  SPRN_PMC1 ; 
 int /*<<< orphan*/  dump_ebb_state () ; 
 int ebb_event_enable (struct event*) ; 
 int /*<<< orphan*/  ebb_is_supported () ; 
 int /*<<< orphan*/  event_close (struct event*) ; 
 int /*<<< orphan*/  event_init_named (struct event*,int,char*) ; 
 int /*<<< orphan*/  event_leader_ebb_init (struct event*) ; 
 int event_open (struct event*) ; 
 int /*<<< orphan*/  mb () ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmc_sample_period (int) ; 
 int sample_period ; 

__attribute__((used)) static int no_handler_test(void)
{
	struct event event;
	u64 val;
	int i;

	SKIP_IF(!ebb_is_supported());

	event_init_named(&event, 0x1001e, "cycles");
	event_leader_ebb_init(&event);

	event.attr.exclude_kernel = 1;
	event.attr.exclude_hv = 1;
	event.attr.exclude_idle = 1;

	FAIL_IF(event_open(&event));
	FAIL_IF(ebb_event_enable(&event));

	val = mfspr(SPRN_EBBHR);
	FAIL_IF(val != 0);

	/* Make sure it overflows quickly */
	sample_period = 1000;
	mtspr(SPRN_PMC1, pmc_sample_period(sample_period));

	/* Spin to make sure the event has time to overflow */
	for (i = 0; i < 1000; i++)
		mb();

	dump_ebb_state();

	/* We expect to see the PMU frozen & PMAO set */
	val = mfspr(SPRN_MMCR0);
	FAIL_IF(val != 0x0000000080000080);

	event_close(&event);

	dump_ebb_state();

	/* The real test is that we never took an EBB at 0x0 */

	return 0;
}