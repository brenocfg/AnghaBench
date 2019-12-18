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
struct tep_record {int dummy; } ;
struct tep_format_field {int dummy; } ;
struct tep_event {int dummy; } ;

/* Variables and functions */
 struct tep_format_field* tep_find_any_field (struct tep_event*,char*) ; 
 scalar_t__ tep_get_field_val (struct trace_seq*,struct tep_event*,char*,struct tep_record*,unsigned long long*,int) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,int) ; 
 int trace_seq_putc (struct trace_seq*,char) ; 
 int /*<<< orphan*/  trace_seq_puts (struct trace_seq*,char*) ; 
 int /*<<< orphan*/  write_and_save_comm (struct tep_format_field*,struct tep_record*,struct trace_seq*,unsigned long long) ; 
 int /*<<< orphan*/  write_state (struct trace_seq*,unsigned long long) ; 

__attribute__((used)) static int sched_switch_handler(struct trace_seq *s,
				struct tep_record *record,
				struct tep_event *event, void *context)
{
	struct tep_format_field *field;
	unsigned long long val;

	if (tep_get_field_val(s, event, "prev_pid", record, &val, 1))
		return trace_seq_putc(s, '!');

	field = tep_find_any_field(event, "prev_comm");
	if (field) {
		write_and_save_comm(field, record, s, val);
		trace_seq_putc(s, ':');
	}
	trace_seq_printf(s, "%lld ", val);

	if (tep_get_field_val(s, event, "prev_prio", record, &val, 0) == 0)
		trace_seq_printf(s, "[%d] ", (int) val);

	if (tep_get_field_val(s,  event, "prev_state", record, &val, 0) == 0)
		write_state(s, val);

	trace_seq_puts(s, " ==> ");

	if (tep_get_field_val(s, event, "next_pid", record, &val, 1))
		return trace_seq_putc(s, '!');

	field = tep_find_any_field(event, "next_comm");
	if (field) {
		write_and_save_comm(field, record, s, val);
		trace_seq_putc(s, ':');
	}
	trace_seq_printf(s, "%lld", val);

	if (tep_get_field_val(s, event, "next_prio", record, &val, 0) == 0)
		trace_seq_printf(s, " [%d]", (int) val);

	return 0;
}