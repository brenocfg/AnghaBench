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
struct trace_buffer_struct {int nesting; char** buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 struct trace_buffer_struct* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_percpu_buffer ; 

__attribute__((used)) static char *get_trace_buf(void)
{
	struct trace_buffer_struct *buffer = this_cpu_ptr(trace_percpu_buffer);

	if (!buffer || buffer->nesting >= 4)
		return NULL;

	buffer->nesting++;

	/* Interrupts must see nesting incremented before we use the buffer */
	barrier();
	return &buffer->buffer[buffer->nesting][0];
}