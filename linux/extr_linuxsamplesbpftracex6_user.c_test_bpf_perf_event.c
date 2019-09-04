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
struct perf_event_attr {int type; int config; int /*<<< orphan*/  sample_type; int /*<<< orphan*/  read_format; int /*<<< orphan*/  inherit; int /*<<< orphan*/  sample_period; int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 int PERF_COUNT_HW_CACHE_L1D ; 
 int PERF_COUNT_HW_CACHE_LL ; 
 int PERF_COUNT_HW_CACHE_OP_READ ; 
 int PERF_COUNT_HW_CACHE_RESULT_ACCESS ; 
 int PERF_COUNT_HW_CACHE_RESULT_MISS ; 
 int PERF_COUNT_HW_CPU_CYCLES ; 
 int PERF_COUNT_SW_CPU_CLOCK ; 
 int PERF_TYPE_HARDWARE ; 
 int PERF_TYPE_HW_CACHE ; 
 int PERF_TYPE_RAW ; 
 int PERF_TYPE_SOFTWARE ; 
 int /*<<< orphan*/  SAMPLE_PERIOD ; 
 int /*<<< orphan*/  test_perf_event_array (struct perf_event_attr*,char*) ; 

__attribute__((used)) static void test_bpf_perf_event(void)
{
	struct perf_event_attr attr_cycles = {
		.freq = 0,
		.sample_period = SAMPLE_PERIOD,
		.inherit = 0,
		.type = PERF_TYPE_HARDWARE,
		.read_format = 0,
		.sample_type = 0,
		.config = PERF_COUNT_HW_CPU_CYCLES,
	};
	struct perf_event_attr attr_clock = {
		.freq = 0,
		.sample_period = SAMPLE_PERIOD,
		.inherit = 0,
		.type = PERF_TYPE_SOFTWARE,
		.read_format = 0,
		.sample_type = 0,
		.config = PERF_COUNT_SW_CPU_CLOCK,
	};
	struct perf_event_attr attr_raw = {
		.freq = 0,
		.sample_period = SAMPLE_PERIOD,
		.inherit = 0,
		.type = PERF_TYPE_RAW,
		.read_format = 0,
		.sample_type = 0,
		/* Intel Instruction Retired */
		.config = 0xc0,
	};
	struct perf_event_attr attr_l1d_load = {
		.freq = 0,
		.sample_period = SAMPLE_PERIOD,
		.inherit = 0,
		.type = PERF_TYPE_HW_CACHE,
		.read_format = 0,
		.sample_type = 0,
		.config =
			PERF_COUNT_HW_CACHE_L1D |
			(PERF_COUNT_HW_CACHE_OP_READ << 8) |
			(PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16),
	};
	struct perf_event_attr attr_llc_miss = {
		.freq = 0,
		.sample_period = SAMPLE_PERIOD,
		.inherit = 0,
		.type = PERF_TYPE_HW_CACHE,
		.read_format = 0,
		.sample_type = 0,
		.config =
			PERF_COUNT_HW_CACHE_LL |
			(PERF_COUNT_HW_CACHE_OP_READ << 8) |
			(PERF_COUNT_HW_CACHE_RESULT_MISS << 16),
	};
	struct perf_event_attr attr_msr_tsc = {
		.freq = 0,
		.sample_period = 0,
		.inherit = 0,
		/* From /sys/bus/event_source/devices/msr/ */
		.type = 7,
		.read_format = 0,
		.sample_type = 0,
		.config = 0,
	};

	test_perf_event_array(&attr_cycles, "HARDWARE-cycles");
	test_perf_event_array(&attr_clock, "SOFTWARE-clock");
	test_perf_event_array(&attr_raw, "RAW-instruction-retired");
	test_perf_event_array(&attr_l1d_load, "HW_CACHE-L1D-load");

	/* below tests may fail in qemu */
	test_perf_event_array(&attr_llc_miss, "HW_CACHE-LLC-miss");
	test_perf_event_array(&attr_msr_tsc, "Dynamic-msr-tsc");
}