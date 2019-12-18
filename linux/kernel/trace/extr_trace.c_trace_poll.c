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
struct trace_iterator {int /*<<< orphan*/  cpu_file; TYPE_1__* trace_buffer; struct trace_array* tr; } ;
struct trace_array {int trace_flags; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_2__ {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int TRACE_ITER_BLOCK ; 
 int ring_buffer_poll_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file*,int /*<<< orphan*/ *) ; 
 scalar_t__ trace_buffer_iter (struct trace_iterator*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __poll_t
trace_poll(struct trace_iterator *iter, struct file *filp, poll_table *poll_table)
{
	struct trace_array *tr = iter->tr;

	/* Iterators are static, they should be filled or empty */
	if (trace_buffer_iter(iter, iter->cpu_file))
		return EPOLLIN | EPOLLRDNORM;

	if (tr->trace_flags & TRACE_ITER_BLOCK)
		/*
		 * Always select as readable when in blocking mode
		 */
		return EPOLLIN | EPOLLRDNORM;
	else
		return ring_buffer_poll_wait(iter->trace_buffer->buffer, iter->cpu_file,
					     filp, poll_table);
}