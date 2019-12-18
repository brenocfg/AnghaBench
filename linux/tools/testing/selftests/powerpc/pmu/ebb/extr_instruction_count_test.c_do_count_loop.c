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
typedef  int uint64_t ;
struct TYPE_5__ {int value; } ;
struct event {TYPE_2__ result; } ;
typedef  int int64_t ;
struct TYPE_4__ {int* pmc_count; int ebb_count; } ;
struct TYPE_6__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int MMCR0_FC ; 
 int /*<<< orphan*/  SPRN_MMCR0 ; 
 int /*<<< orphan*/  clear_ebb_stats () ; 
 int /*<<< orphan*/  count_pmc (int,int /*<<< orphan*/ ) ; 
 int counters_frozen ; 
 TYPE_3__ ebb_state ; 
 int /*<<< orphan*/  mb () ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  sample_period ; 
 int /*<<< orphan*/  thirty_two_instruction_loop (int) ; 

__attribute__((used)) static int do_count_loop(struct event *event, uint64_t instructions,
			 uint64_t overhead, bool report)
{
	int64_t difference, expected;
	double percentage;

	clear_ebb_stats();

	counters_frozen = false;
	mb();
	mtspr(SPRN_MMCR0, mfspr(SPRN_MMCR0) & ~MMCR0_FC);

	thirty_two_instruction_loop(instructions >> 5);

	counters_frozen = true;
	mb();
	mtspr(SPRN_MMCR0, mfspr(SPRN_MMCR0) | MMCR0_FC);

	count_pmc(4, sample_period);

	event->result.value = ebb_state.stats.pmc_count[4-1];
	expected = instructions + overhead;
	difference = event->result.value - expected;
	percentage = (double)difference / event->result.value * 100;

	if (report) {
		printf("Looped for %lu instructions, overhead %lu\n", instructions, overhead);
		printf("Expected %lu\n", expected);
		printf("Actual   %llu\n", event->result.value);
		printf("Delta    %ld, %f%%\n", difference, percentage);
		printf("Took %d EBBs\n", ebb_state.stats.ebb_count);
	}

	if (difference < 0)
		difference = -difference;

	/* Tolerate a difference of up to 0.0001 % */
	difference *= 10000 * 100;
	if (difference / event->result.value)
		return -1;

	return 0;
}