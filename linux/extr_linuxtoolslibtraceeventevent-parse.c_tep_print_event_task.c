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
struct tep_record {int /*<<< orphan*/  cpu; void* data; } ;
struct tep_handle {scalar_t__ latency_format; } ;
struct event_format {int dummy; } ;

/* Variables and functions */
 char* find_cmdline (struct tep_handle*,int) ; 
 int parse_common_pid (struct tep_handle*,void*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,char const*,int,int /*<<< orphan*/ ) ; 

void tep_print_event_task(struct tep_handle *pevent, struct trace_seq *s,
			  struct event_format *event,
			  struct tep_record *record)
{
	void *data = record->data;
	const char *comm;
	int pid;

	pid = parse_common_pid(pevent, data);
	comm = find_cmdline(pevent, pid);

	if (pevent->latency_format) {
		trace_seq_printf(s, "%8.8s-%-5d %3d",
		       comm, pid, record->cpu);
	} else
		trace_seq_printf(s, "%16s-%-5d [%03d]", comm, pid, record->cpu);
}