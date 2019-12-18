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
struct perf_event_attr {int size; unsigned long bp_addr; int bp_len; int sample_period; int exclude_kernel; int exclude_hv; scalar_t__ config; int /*<<< orphan*/  sample_type; int /*<<< orphan*/  bp_type; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_BREAKPOINT_W ; 
 int /*<<< orphan*/  HW_BREAKPOINT_X ; 
 int /*<<< orphan*/  PERF_SAMPLE_IP ; 
 int /*<<< orphan*/  PERF_TYPE_BREAKPOINT ; 
 int TEST_FAIL ; 
 int /*<<< orphan*/  memset (struct perf_event_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perf_event_open_cloexec_flag () ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 int sys_perf_event_open (struct perf_event_attr*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __event(bool is_x, void *addr, struct perf_event_attr *attr)
{
	int fd;

	memset(attr, 0, sizeof(struct perf_event_attr));
	attr->type = PERF_TYPE_BREAKPOINT;
	attr->size = sizeof(struct perf_event_attr);

	attr->config = 0;
	attr->bp_type = is_x ? HW_BREAKPOINT_X : HW_BREAKPOINT_W;
	attr->bp_addr = (unsigned long) addr;
	attr->bp_len = sizeof(long);

	attr->sample_period = 1;
	attr->sample_type = PERF_SAMPLE_IP;

	attr->exclude_kernel = 1;
	attr->exclude_hv = 1;

	fd = sys_perf_event_open(attr, -1, 0, -1,
				 perf_event_open_cloexec_flag());
	if (fd < 0) {
		pr_debug("failed opening event %llx\n", attr->config);
		return TEST_FAIL;
	}

	return fd;
}