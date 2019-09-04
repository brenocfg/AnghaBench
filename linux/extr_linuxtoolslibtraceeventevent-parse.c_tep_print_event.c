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
struct tep_record {int size; scalar_t__ data; } ;
struct tep_handle {int dummy; } ;
struct event_format {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_warning (char*,int) ; 
 struct event_format* tep_find_event_by_record (struct tep_handle*,struct tep_record*) ; 
 int /*<<< orphan*/  tep_print_event_data (struct tep_handle*,struct trace_seq*,struct event_format*,struct tep_record*) ; 
 int /*<<< orphan*/  tep_print_event_task (struct tep_handle*,struct trace_seq*,struct event_format*,struct tep_record*) ; 
 int /*<<< orphan*/  tep_print_event_time (struct tep_handle*,struct trace_seq*,struct event_format*,struct tep_record*,int) ; 
 int trace_parse_common_type (struct tep_handle*,scalar_t__) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,unsigned char) ; 

void tep_print_event(struct tep_handle *pevent, struct trace_seq *s,
		     struct tep_record *record, bool use_trace_clock)
{
	struct event_format *event;

	event = tep_find_event_by_record(pevent, record);
	if (!event) {
		int i;
		int type = trace_parse_common_type(pevent, record->data);

		do_warning("ug! no event found for type %d", type);
		trace_seq_printf(s, "[UNKNOWN TYPE %d]", type);
		for (i = 0; i < record->size; i++)
			trace_seq_printf(s, " %02x",
					 ((unsigned char *)record->data)[i]);
		return;
	}

	tep_print_event_task(pevent, s, event, record);
	tep_print_event_time(pevent, s, event, record, use_trace_clock);
	tep_print_event_data(pevent, s, event, record);
}