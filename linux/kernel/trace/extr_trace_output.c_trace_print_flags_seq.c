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
struct trace_print_flags {char* name; unsigned long mask; } ;

/* Variables and functions */
 char* trace_seq_buffer_ptr (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,unsigned long) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_seq_puts (struct trace_seq*,char const*) ; 

const char *
trace_print_flags_seq(struct trace_seq *p, const char *delim,
		      unsigned long flags,
		      const struct trace_print_flags *flag_array)
{
	unsigned long mask;
	const char *str;
	const char *ret = trace_seq_buffer_ptr(p);
	int i, first = 1;

	for (i = 0;  flag_array[i].name && flags; i++) {

		mask = flag_array[i].mask;
		if ((flags & mask) != mask)
			continue;

		str = flag_array[i].name;
		flags &= ~mask;
		if (!first && delim)
			trace_seq_puts(p, delim);
		else
			first = 0;
		trace_seq_puts(p, str);
	}

	/* check for left over flags */
	if (flags) {
		if (!first && delim)
			trace_seq_puts(p, delim);
		trace_seq_printf(p, "0x%lx", flags);
	}

	trace_seq_putc(p, 0);

	return ret;
}