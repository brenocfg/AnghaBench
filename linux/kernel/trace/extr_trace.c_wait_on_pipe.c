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
struct trace_iterator {int /*<<< orphan*/  cpu_file; TYPE_1__* trace_buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int ring_buffer_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ trace_buffer_iter (struct trace_iterator*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wait_on_pipe(struct trace_iterator *iter, int full)
{
	/* Iterators are static, they should be filled or empty */
	if (trace_buffer_iter(iter, iter->cpu_file))
		return 0;

	return ring_buffer_wait(iter->trace_buffer->buffer, iter->cpu_file,
				full);
}