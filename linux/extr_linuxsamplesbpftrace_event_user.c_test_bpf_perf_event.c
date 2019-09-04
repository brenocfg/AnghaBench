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
struct perf_event_attr {int freq; int config; int precise_ip; int /*<<< orphan*/  sample_type; int /*<<< orphan*/  type; int /*<<< orphan*/  sample_freq; } ;

/* Variables and functions */
 int PERF_COUNT_HW_CACHE_BPU ; 
 int PERF_COUNT_HW_CACHE_L1D ; 
 int PERF_COUNT_HW_CACHE_OP_READ ; 
 int PERF_COUNT_HW_CACHE_RESULT_ACCESS ; 
 int PERF_COUNT_HW_CACHE_RESULT_MISS ; 
 int PERF_COUNT_HW_CPU_CYCLES ; 
 int PERF_COUNT_SW_CPU_CLOCK ; 
 int /*<<< orphan*/  PERF_SAMPLE_ADDR ; 
 int /*<<< orphan*/  PERF_TYPE_HARDWARE ; 
 int /*<<< orphan*/  PERF_TYPE_HW_CACHE ; 
 int /*<<< orphan*/  PERF_TYPE_RAW ; 
 int /*<<< orphan*/  PERF_TYPE_SOFTWARE ; 
 int /*<<< orphan*/  SAMPLE_FREQ ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  test_perf_event_all_cpu (struct perf_event_attr*) ; 
 int /*<<< orphan*/  test_perf_event_task (struct perf_event_attr*) ; 

__attribute__((used)) static void test_bpf_perf_event(void)
{
	struct perf_event_attr attr_type_hw = {
		.sample_freq = SAMPLE_FREQ,
		.freq = 1,
		.type = PERF_TYPE_HARDWARE,
		.config = PERF_COUNT_HW_CPU_CYCLES,
	};
	struct perf_event_attr attr_type_sw = {
		.sample_freq = SAMPLE_FREQ,
		.freq = 1,
		.type = PERF_TYPE_SOFTWARE,
		.config = PERF_COUNT_SW_CPU_CLOCK,
	};
	struct perf_event_attr attr_hw_cache_l1d = {
		.sample_freq = SAMPLE_FREQ,
		.freq = 1,
		.type = PERF_TYPE_HW_CACHE,
		.config =
			PERF_COUNT_HW_CACHE_L1D |
			(PERF_COUNT_HW_CACHE_OP_READ << 8) |
			(PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16),
	};
	struct perf_event_attr attr_hw_cache_branch_miss = {
		.sample_freq = SAMPLE_FREQ,
		.freq = 1,
		.type = PERF_TYPE_HW_CACHE,
		.config =
			PERF_COUNT_HW_CACHE_BPU |
			(PERF_COUNT_HW_CACHE_OP_READ << 8) |
			(PERF_COUNT_HW_CACHE_RESULT_MISS << 16),
	};
	struct perf_event_attr attr_type_raw = {
		.sample_freq = SAMPLE_FREQ,
		.freq = 1,
		.type = PERF_TYPE_RAW,
		/* Intel Instruction Retired */
		.config = 0xc0,
	};
	struct perf_event_attr attr_type_raw_lock_load = {
		.sample_freq = SAMPLE_FREQ,
		.freq = 1,
		.type = PERF_TYPE_RAW,
		/* Intel MEM_UOPS_RETIRED.LOCK_LOADS */
		.config = 0x21d0,
		/* Request to record lock address from PEBS */
		.sample_type = PERF_SAMPLE_ADDR,
		/* Record address value requires precise event */
		.precise_ip = 2,
	};

	printf("Test HW_CPU_CYCLES\n");
	test_perf_event_all_cpu(&attr_type_hw);
	test_perf_event_task(&attr_type_hw);

	printf("Test SW_CPU_CLOCK\n");
	test_perf_event_all_cpu(&attr_type_sw);
	test_perf_event_task(&attr_type_sw);

	printf("Test HW_CACHE_L1D\n");
	test_perf_event_all_cpu(&attr_hw_cache_l1d);
	test_perf_event_task(&attr_hw_cache_l1d);

	printf("Test HW_CACHE_BPU\n");
	test_perf_event_all_cpu(&attr_hw_cache_branch_miss);
	test_perf_event_task(&attr_hw_cache_branch_miss);

	printf("Test Instruction Retired\n");
	test_perf_event_all_cpu(&attr_type_raw);
	test_perf_event_task(&attr_type_raw);

	printf("Test Lock Load\n");
	test_perf_event_all_cpu(&attr_type_raw_lock_load);
	test_perf_event_task(&attr_type_raw_lock_load);

	printf("*** PASS ***\n");
}