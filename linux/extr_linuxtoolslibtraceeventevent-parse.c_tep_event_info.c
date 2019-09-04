#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct trace_seq {int dummy; } ;
struct tep_record {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct event_format {int flags; int (* handler ) (struct trace_seq*,struct tep_record*,struct event_format*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  context; TYPE_1__* pevent; } ;
struct TYPE_2__ {scalar_t__ print_raw; } ;

/* Variables and functions */
 int EVENT_FL_NOHANDLE ; 
 int EVENT_FL_PRINTRAW ; 
 int /*<<< orphan*/  pretty_print (struct trace_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct event_format*) ; 
 int stub1 (struct trace_seq*,struct tep_record*,struct event_format*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tep_print_fields (struct trace_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct event_format*) ; 
 int /*<<< orphan*/  trace_seq_terminate (struct trace_seq*) ; 

void tep_event_info(struct trace_seq *s, struct event_format *event,
		    struct tep_record *record)
{
	int print_pretty = 1;

	if (event->pevent->print_raw || (event->flags & EVENT_FL_PRINTRAW))
		tep_print_fields(s, record->data, record->size, event);
	else {

		if (event->handler && !(event->flags & EVENT_FL_NOHANDLE))
			print_pretty = event->handler(s, record, event,
						      event->context);

		if (print_pretty)
			pretty_print(s, record->data, record->size, event);
	}

	trace_seq_terminate(s);
}