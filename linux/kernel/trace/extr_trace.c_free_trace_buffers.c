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
struct trace_array {int /*<<< orphan*/  max_buffer; int /*<<< orphan*/  trace_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_trace_buffer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_trace_buffers(struct trace_array *tr)
{
	if (!tr)
		return;

	free_trace_buffer(&tr->trace_buffer);

#ifdef CONFIG_TRACER_MAX_TRACE
	free_trace_buffer(&tr->max_buffer);
#endif
}