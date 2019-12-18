#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ buffer; } ;
struct trace_array {int clock_id; TYPE_1__ max_buffer; TYPE_1__ trace_buffer; } ;
struct TYPE_5__ {int /*<<< orphan*/  func; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring_buffer_set_clock (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 TYPE_2__* trace_clocks ; 
 int /*<<< orphan*/  trace_types_lock ; 
 int /*<<< orphan*/  tracing_reset_online_cpus (TYPE_1__*) ; 

int tracing_set_clock(struct trace_array *tr, const char *clockstr)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(trace_clocks); i++) {
		if (strcmp(trace_clocks[i].name, clockstr) == 0)
			break;
	}
	if (i == ARRAY_SIZE(trace_clocks))
		return -EINVAL;

	mutex_lock(&trace_types_lock);

	tr->clock_id = i;

	ring_buffer_set_clock(tr->trace_buffer.buffer, trace_clocks[i].func);

	/*
	 * New clock may not be consistent with the previous clock.
	 * Reset the buffer so that it doesn't have incomparable timestamps.
	 */
	tracing_reset_online_cpus(&tr->trace_buffer);

#ifdef CONFIG_TRACER_MAX_TRACE
	if (tr->max_buffer.buffer)
		ring_buffer_set_clock(tr->max_buffer.buffer, trace_clocks[i].func);
	tracing_reset_online_cpus(&tr->max_buffer);
#endif

	mutex_unlock(&trace_types_lock);

	return 0;
}