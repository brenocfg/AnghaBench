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
struct trace_buffer {int /*<<< orphan*/  buffer; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {scalar_t__ skipped_entries; } ;

/* Variables and functions */
 TYPE_1__* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 unsigned long ring_buffer_entries_cpu (int /*<<< orphan*/ ,int) ; 
 unsigned long ring_buffer_overrun_cpu (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
get_total_entries_cpu(struct trace_buffer *buf, unsigned long *total,
		      unsigned long *entries, int cpu)
{
	unsigned long count;

	count = ring_buffer_entries_cpu(buf->buffer, cpu);
	/*
	 * If this buffer has skipped entries, then we hold all
	 * entries for the trace and we need to ignore the
	 * ones before the time stamp.
	 */
	if (per_cpu_ptr(buf->data, cpu)->skipped_entries) {
		count -= per_cpu_ptr(buf->data, cpu)->skipped_entries;
		/* total is the same as the entries */
		*total = count;
	} else
		*total = count +
			ring_buffer_overrun_cpu(buf->buffer, cpu);
	*entries = count;
}