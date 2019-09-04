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
struct oprofile_cpu_buffer {int /*<<< orphan*/  backtrace_aborted; scalar_t__ tracing; } ;

/* Variables and functions */
 unsigned long ESCAPE_CODE ; 
 scalar_t__ op_add_sample (struct oprofile_cpu_buffer*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  op_cpu_buffer ; 
 struct oprofile_cpu_buffer* this_cpu_ptr (int /*<<< orphan*/ *) ; 

void oprofile_add_trace(unsigned long pc)
{
	struct oprofile_cpu_buffer *cpu_buf = this_cpu_ptr(&op_cpu_buffer);

	if (!cpu_buf->tracing)
		return;

	/*
	 * broken frame can give an eip with the same value as an
	 * escape code, abort the trace if we get it
	 */
	if (pc == ESCAPE_CODE)
		goto fail;

	if (op_add_sample(cpu_buf, pc, 0))
		goto fail;

	return;
fail:
	cpu_buf->tracing = 0;
	cpu_buf->backtrace_aborted++;
	return;
}