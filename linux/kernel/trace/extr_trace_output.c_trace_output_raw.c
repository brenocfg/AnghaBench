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
typedef  int /*<<< orphan*/  va_list ;
struct trace_seq {int dummy; } ;
struct trace_iterator {struct trace_seq seq; } ;

/* Variables and functions */
 int trace_handle_return (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,char*) ; 
 int /*<<< orphan*/  trace_seq_vprintf (struct trace_seq*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trace_output_raw(struct trace_iterator *iter, char *name,
			    char *fmt, va_list ap)
{
	struct trace_seq *s = &iter->seq;

	trace_seq_printf(s, "%s: ", name);
	trace_seq_vprintf(s, fmt, ap);

	return trace_handle_return(s);
}