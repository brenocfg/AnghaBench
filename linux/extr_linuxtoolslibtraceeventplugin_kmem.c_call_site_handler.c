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
struct tep_record {void* data; } ;
struct format_field {int dummy; } ;
struct event_format {int /*<<< orphan*/  pevent; } ;

/* Variables and functions */
 struct format_field* tep_find_field (struct event_format*,char*) ; 
 char* tep_find_function (int /*<<< orphan*/ ,unsigned long long) ; 
 unsigned long long tep_find_function_address (int /*<<< orphan*/ ,unsigned long long) ; 
 scalar_t__ tep_read_number_field (struct format_field*,void*,unsigned long long*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,char const*,int) ; 

__attribute__((used)) static int call_site_handler(struct trace_seq *s, struct tep_record *record,
			     struct event_format *event, void *context)
{
	struct format_field *field;
	unsigned long long val, addr;
	void *data = record->data;
	const char *func;

	field = tep_find_field(event, "call_site");
	if (!field)
		return 1;

	if (tep_read_number_field(field, data, &val))
		return 1;

	func = tep_find_function(event->pevent, val);
	if (!func)
		return 1;

	addr = tep_find_function_address(event->pevent, val);

	trace_seq_printf(s, "(%s+0x%x) ", func, (int)(val - addr));
	return 1;
}