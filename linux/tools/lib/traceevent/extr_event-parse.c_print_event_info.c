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
struct tep_record {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct tep_event {int flags; int (* handler ) (struct trace_seq*,struct tep_record*,struct tep_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int TEP_EVENT_FL_NOHANDLE ; 
 int TEP_EVENT_FL_PRINTRAW ; 
 int /*<<< orphan*/  pretty_print (struct trace_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tep_event*) ; 
 int stub1 (struct trace_seq*,struct tep_record*,struct tep_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tep_print_fields (struct trace_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tep_event*) ; 
 int /*<<< orphan*/  trace_seq_terminate (struct trace_seq*) ; 

__attribute__((used)) static void print_event_info(struct trace_seq *s, char *format, bool raw,
			     struct tep_event *event, struct tep_record *record)
{
	int print_pretty = 1;

	if (raw || (event->flags & TEP_EVENT_FL_PRINTRAW))
		tep_print_fields(s, record->data, record->size, event);
	else {

		if (event->handler && !(event->flags & TEP_EVENT_FL_NOHANDLE))
			print_pretty = event->handler(s, record, event,
						      event->context);

		if (print_pretty)
			pretty_print(s, record->data, record->size, event);
	}

	trace_seq_terminate(s);
}