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
struct tep_record {int cpu; int /*<<< orphan*/  data; } ;
struct tep_handle {int dummy; } ;
struct tep_event {int dummy; } ;
struct print_event_type {int /*<<< orphan*/  format; } ;

/* Variables and functions */
#define  TEP_PRINT_CPU 130 
#define  TEP_PRINT_PID 129 
#define  TEP_PRINT_TIME 128 
 int parse_common_pid (struct tep_handle*,int /*<<< orphan*/ ) ; 
 void print_event_time (struct tep_handle*,struct trace_seq*,int /*<<< orphan*/ ,struct tep_event*,struct tep_record*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void print_int(struct tep_handle *tep, struct trace_seq *s,
		      struct tep_record *record, struct tep_event *event,
		      int arg, struct print_event_type *type)
{
	int param;

	switch (arg) {
	case TEP_PRINT_CPU:
		param = record->cpu;
		break;
	case TEP_PRINT_PID:
		param = parse_common_pid(tep, record->data);
		break;
	case TEP_PRINT_TIME:
		return print_event_time(tep, s, type->format, event, record);
	default:
		return;
	}
	trace_seq_printf(s, type->format, param);
}