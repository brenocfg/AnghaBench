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
struct trace_iterator {scalar_t__ ent_size; scalar_t__ ent; struct trace_seq seq; } ;
struct trace_event {int dummy; } ;
struct stack_entry {unsigned long* caller; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;

/* Variables and functions */
 unsigned long ULONG_MAX ; 
 int /*<<< orphan*/  seq_print_ip_sym (struct trace_seq*,unsigned long,int) ; 
 int /*<<< orphan*/  trace_assign_type (struct stack_entry*,scalar_t__) ; 
 int trace_handle_return (struct trace_seq*) ; 
 scalar_t__ trace_seq_has_overflowed (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,char) ; 
 int /*<<< orphan*/  trace_seq_puts (struct trace_seq*,char*) ; 

__attribute__((used)) static enum print_line_t trace_stack_print(struct trace_iterator *iter,
					   int flags, struct trace_event *event)
{
	struct stack_entry *field;
	struct trace_seq *s = &iter->seq;
	unsigned long *p;
	unsigned long *end;

	trace_assign_type(field, iter->ent);
	end = (unsigned long *)((long)iter->ent + iter->ent_size);

	trace_seq_puts(s, "<stack trace>\n");

	for (p = field->caller; p && p < end && *p != ULONG_MAX; p++) {

		if (trace_seq_has_overflowed(s))
			break;

		trace_seq_puts(s, " => ");
		seq_print_ip_sym(s, *p, flags);
		trace_seq_putc(s, '\n');
	}

	return trace_handle_return(s);
}