#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMCR0_FC ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  SPRN_MMCR0 ; 
 int /*<<< orphan*/  SPRN_PMC1 ; 
 int /*<<< orphan*/  child () ; 
 int /*<<< orphan*/  ebb_enable_pmc_counting (int) ; 
 int /*<<< orphan*/  ebb_event_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ebb_global_enable () ; 
 int /*<<< orphan*/  ebb_is_supported () ; 
 int /*<<< orphan*/  event ; 
 int /*<<< orphan*/  event_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_init_named (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  event_leader_ebb_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmc_sample_period (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sample_period ; 
 int /*<<< orphan*/  setup_ebb_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  standard_ebb_callee ; 
 int /*<<< orphan*/  wait_for_child (scalar_t__) ; 

int fork_cleanup(void)
{
	pid_t pid;

	SKIP_IF(!ebb_is_supported());

	event_init_named(&event, 0x1001e, "cycles");
	event_leader_ebb_init(&event);

	FAIL_IF(event_open(&event));

	ebb_enable_pmc_counting(1);
	setup_ebb_handler(standard_ebb_callee);
	ebb_global_enable();

	FAIL_IF(ebb_event_enable(&event));

	mtspr(SPRN_MMCR0, MMCR0_FC);
	mtspr(SPRN_PMC1, pmc_sample_period(sample_period));

	/* Don't need to actually take any EBBs */

	pid = fork();
	if (pid == 0)
		exit(child());

	/* Child does the actual testing */
	FAIL_IF(wait_for_child(pid));

	/* After fork */
	event_close(&event);

	return 0;
}