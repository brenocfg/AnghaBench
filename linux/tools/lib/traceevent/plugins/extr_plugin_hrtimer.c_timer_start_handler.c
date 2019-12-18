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
struct tep_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tep_print_func_field (struct trace_seq*,char*,struct tep_event*,char*,struct tep_record*,int /*<<< orphan*/ ) ; 
 int tep_print_num_field (struct trace_seq*,char*,struct tep_event*,char*,struct tep_record*,int) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*) ; 

__attribute__((used)) static int timer_start_handler(struct trace_seq *s,
			       struct tep_record *record,
			       struct tep_event *event, void *context)
{
	trace_seq_printf(s, "hrtimer=");

	if (tep_print_num_field(s, "0x%llx", event, "timer",
				record, 0) == -1)
		tep_print_num_field(s, "0x%llx", event, "hrtimer",
				    record, 1);

	tep_print_func_field(s, " function=%s", event, "function",
			     record, 0);

	trace_seq_printf(s, " expires=");
	tep_print_num_field(s, "%llu", event, "expires", record, 1);

	trace_seq_printf(s, " softexpires=");
	tep_print_num_field(s, "%llu", event, "softexpires", record, 1);
	return 0;
}