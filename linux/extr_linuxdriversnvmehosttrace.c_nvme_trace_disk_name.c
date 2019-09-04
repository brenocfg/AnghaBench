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
 char* trace_seq_buffer_ptr (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,char*) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,int /*<<< orphan*/ ) ; 

const char *nvme_trace_disk_name(struct trace_seq *p, char *name)
{
	const char *ret = trace_seq_buffer_ptr(p);

	if (*name)
		trace_seq_printf(p, "disk=%s, ", name);
	trace_seq_putc(p, 0);

	return ret;
}