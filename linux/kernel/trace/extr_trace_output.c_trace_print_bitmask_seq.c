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
struct trace_seq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_seq_bitmask (struct trace_seq*,void*,unsigned int) ; 
 char* trace_seq_buffer_ptr (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,int /*<<< orphan*/ ) ; 

const char *
trace_print_bitmask_seq(struct trace_seq *p, void *bitmask_ptr,
			unsigned int bitmask_size)
{
	const char *ret = trace_seq_buffer_ptr(p);

	trace_seq_bitmask(p, bitmask_ptr, bitmask_size * 8);
	trace_seq_putc(p, 0);

	return ret;
}