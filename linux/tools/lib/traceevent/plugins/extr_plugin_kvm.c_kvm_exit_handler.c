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
 scalar_t__ print_exit_reason (struct trace_seq*,struct tep_record*,struct tep_event*,char*) ; 
 scalar_t__ tep_get_field_val (struct trace_seq*,struct tep_event*,char*,struct tep_record*,unsigned long long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tep_print_num_field (struct trace_seq*,char*,struct tep_event*,char*,struct tep_record*,int) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,unsigned long long,unsigned long long) ; 

__attribute__((used)) static int kvm_exit_handler(struct trace_seq *s, struct tep_record *record,
			    struct tep_event *event, void *context)
{
	unsigned long long info1 = 0, info2 = 0;

	if (print_exit_reason(s, record, event, "exit_reason") < 0)
		return -1;

	tep_print_num_field(s, " rip 0x%lx", event, "guest_rip", record, 1);

	if (tep_get_field_val(s, event, "info1", record, &info1, 0) >= 0
	    && tep_get_field_val(s, event, "info2", record, &info2, 0) >= 0)
		trace_seq_printf(s, " info %llx %llx", info1, info2);

	return 0;
}