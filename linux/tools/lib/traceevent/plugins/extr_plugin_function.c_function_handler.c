#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct trace_seq {int dummy; } ;
struct tep_record {int /*<<< orphan*/  cpu; } ;
struct tep_handle {int dummy; } ;
struct tep_event {struct tep_handle* tep; } ;
struct TYPE_4__ {scalar_t__ set; } ;
struct TYPE_3__ {scalar_t__ set; } ;

/* Variables and functions */
 int add_and_get_index (char const*,char const*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ftrace_indent ; 
 TYPE_1__* ftrace_parent ; 
 char* tep_find_function (struct tep_handle*,unsigned long long) ; 
 scalar_t__ tep_get_field_val (struct trace_seq*,struct tep_event*,char*,struct tep_record*,unsigned long long*,int) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,...) ; 
 int trace_seq_putc (struct trace_seq*,char) ; 

__attribute__((used)) static int function_handler(struct trace_seq *s, struct tep_record *record,
			    struct tep_event *event, void *context)
{
	struct tep_handle *tep = event->tep;
	unsigned long long function;
	unsigned long long pfunction;
	const char *func;
	const char *parent;
	int index = 0;

	if (tep_get_field_val(s, event, "ip", record, &function, 1))
		return trace_seq_putc(s, '!');

	func = tep_find_function(tep, function);

	if (tep_get_field_val(s, event, "parent_ip", record, &pfunction, 1))
		return trace_seq_putc(s, '!');

	parent = tep_find_function(tep, pfunction);

	if (parent && ftrace_indent->set)
		index = add_and_get_index(parent, func, record->cpu);

	trace_seq_printf(s, "%*s", index*3, "");

	if (func)
		trace_seq_printf(s, "%s", func);
	else
		trace_seq_printf(s, "0x%llx", function);

	if (ftrace_parent->set) {
		trace_seq_printf(s, " <-- ");
		if (parent)
			trace_seq_printf(s, "%s", parent);
		else
			trace_seq_printf(s, "0x%llx", pfunction);
	}

	return 0;
}