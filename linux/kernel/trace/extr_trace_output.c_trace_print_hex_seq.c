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
 int /*<<< orphan*/  min (int,int) ; 
 char* trace_seq_buffer_ptr (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char const*,int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,int /*<<< orphan*/ ) ; 

const char *
trace_print_hex_seq(struct trace_seq *p, const unsigned char *buf, int buf_len,
		    bool concatenate)
{
	int i;
	const char *ret = trace_seq_buffer_ptr(p);
	const char *fmt = concatenate ? "%*phN" : "%*ph";

	for (i = 0; i < buf_len; i += 16)
		trace_seq_printf(p, fmt, min(buf_len - i, 16), &buf[i]);
	trace_seq_putc(p, 0);

	return ret;
}