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
struct trace_iterator {struct trace_entry* ent; struct trace_seq seq; } ;
struct trace_entry {int dummy; } ;
struct bputs_entry {int /*<<< orphan*/  str; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;

/* Variables and functions */
 int /*<<< orphan*/  trace_assign_type (struct bputs_entry*,struct trace_entry*) ; 
 int trace_handle_return (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_puts (struct trace_seq*,int /*<<< orphan*/ ) ; 

enum print_line_t trace_print_bputs_msg_only(struct trace_iterator *iter)
{
	struct trace_seq *s = &iter->seq;
	struct trace_entry *entry = iter->ent;
	struct bputs_entry *field;

	trace_assign_type(field, entry);

	trace_seq_puts(s, field->str);

	return trace_handle_return(s);
}