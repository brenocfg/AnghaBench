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
typedef  int uint64_t ;
struct perf_event_attr {int sample_regs_intr; int precise_ip; int disabled; int exclude_kernel; int sample_period; int /*<<< orphan*/  sample_type; int /*<<< orphan*/  config; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_COUNT_HW_CPU_CYCLES ; 
 int PERF_REGS_MASK ; 
 int PERF_REG_EXTENDED_MASK ; 
 int /*<<< orphan*/  PERF_SAMPLE_REGS_INTR ; 
 int /*<<< orphan*/  PERF_TYPE_HARDWARE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  event_attr_init (struct perf_event_attr*) ; 
 int sys_perf_event_open (struct perf_event_attr*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

uint64_t arch__intr_reg_mask(void)
{
	struct perf_event_attr attr = {
		.type			= PERF_TYPE_HARDWARE,
		.config			= PERF_COUNT_HW_CPU_CYCLES,
		.sample_type		= PERF_SAMPLE_REGS_INTR,
		.sample_regs_intr	= PERF_REG_EXTENDED_MASK,
		.precise_ip		= 1,
		.disabled 		= 1,
		.exclude_kernel		= 1,
	};
	int fd;
	/*
	 * In an unnamed union, init it here to build on older gcc versions
	 */
	attr.sample_period = 1;

	event_attr_init(&attr);

	fd = sys_perf_event_open(&attr, 0, -1, -1, 0);
	if (fd != -1) {
		close(fd);
		return (PERF_REG_EXTENDED_MASK | PERF_REGS_MASK);
	}

	return PERF_REGS_MASK;
}