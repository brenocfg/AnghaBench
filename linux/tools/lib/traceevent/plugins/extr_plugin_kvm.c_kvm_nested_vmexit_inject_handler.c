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
 int /*<<< orphan*/  tep_print_num_field (struct trace_seq*,char*,struct tep_event*,char*,struct tep_record*,int) ; 

__attribute__((used)) static int kvm_nested_vmexit_inject_handler(struct trace_seq *s, struct tep_record *record,
					    struct tep_event *event, void *context)
{
	if (print_exit_reason(s, record, event, "exit_code") < 0)
		return -1;

	tep_print_num_field(s, " info1 %llx", event, "exit_info1", record, 1);
	tep_print_num_field(s, " info2 %llx", event, "exit_info2", record, 1);
	tep_print_num_field(s, " int_info %llx", event, "exit_int_info", record, 1);
	tep_print_num_field(s, " int_info_err %llx", event, "exit_int_info_err", record, 1);

	return 0;
}