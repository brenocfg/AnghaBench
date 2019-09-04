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
struct trace_iterator {struct trace_seq seq; struct trace_entry* ent; } ;
struct trace_event {int dummy; } ;
struct trace_entry {int dummy; } ;
struct bputs_entry {char* str; int /*<<< orphan*/  ip; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;

/* Variables and functions */
 int /*<<< orphan*/  seq_print_ip_sym (struct trace_seq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_assign_type (struct bputs_entry*,struct trace_entry*) ; 
 int trace_handle_return (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_puts (struct trace_seq*,char*) ; 

__attribute__((used)) static enum print_line_t
trace_bputs_print(struct trace_iterator *iter, int flags,
		   struct trace_event *event)
{
	struct trace_entry *entry = iter->ent;
	struct trace_seq *s = &iter->seq;
	struct bputs_entry *field;

	trace_assign_type(field, entry);

	seq_print_ip_sym(s, field->ip, flags);
	trace_seq_puts(s, ": ");
	trace_seq_puts(s, field->str);

	return trace_handle_return(s);
}