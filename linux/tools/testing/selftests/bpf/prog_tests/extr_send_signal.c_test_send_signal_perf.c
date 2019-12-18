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
struct perf_event_attr {int sample_period; int /*<<< orphan*/  config; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_TYPE_PERF_EVENT ; 
 int /*<<< orphan*/  PERF_COUNT_SW_CPU_CLOCK ; 
 int /*<<< orphan*/  PERF_TYPE_SOFTWARE ; 
 int /*<<< orphan*/  test_send_signal_common (struct perf_event_attr*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_send_signal_perf(void)
{
	struct perf_event_attr attr = {
		.sample_period = 1,
		.type = PERF_TYPE_SOFTWARE,
		.config = PERF_COUNT_SW_CPU_CLOCK,
	};

	test_send_signal_common(&attr, BPF_PROG_TYPE_PERF_EVENT,
				"perf_sw_event");
}