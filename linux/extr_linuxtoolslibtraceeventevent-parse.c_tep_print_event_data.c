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
struct tep_handle {int dummy; } ;
struct event_format {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tep_event_info (struct trace_seq*,struct event_format*,struct tep_record*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,int,...) ; 

void tep_print_event_data(struct tep_handle *pevent, struct trace_seq *s,
			  struct event_format *event,
			  struct tep_record *record)
{
	static const char *spaces = "                    "; /* 20 spaces */
	int len;

	trace_seq_printf(s, " %s: ", event->name);

	/* Space out the event names evenly. */
	len = strlen(event->name);
	if (len < 20)
		trace_seq_printf(s, "%.*s", 20 - len, spaces);

	tep_event_info(s, event, record);
}