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
struct tep_record {int /*<<< orphan*/  data; } ;
struct tep_handle {int dummy; } ;
struct func_map {char* func; scalar_t__ addr; } ;
struct format_field {int dummy; } ;
struct event_format {struct tep_handle* pevent; } ;

/* Variables and functions */
 struct func_map* find_func (struct tep_handle*,unsigned long long) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long) ; 
 struct format_field* tep_find_field (struct event_format*,char const*) ; 
 scalar_t__ tep_read_number_field (struct format_field*,int /*<<< orphan*/ ,unsigned long long*) ; 
 int trace_seq_printf (struct trace_seq*,char const*,char const*) ; 

int tep_print_func_field(struct trace_seq *s, const char *fmt,
			 struct event_format *event, const char *name,
			 struct tep_record *record, int err)
{
	struct format_field *field = tep_find_field(event, name);
	struct tep_handle *pevent = event->pevent;
	unsigned long long val;
	struct func_map *func;
	char tmp[128];

	if (!field)
		goto failed;

	if (tep_read_number_field(field, record->data, &val))
		goto failed;

	func = find_func(pevent, val);

	if (func)
		snprintf(tmp, 128, "%s/0x%llx", func->func, func->addr - val);
	else
		sprintf(tmp, "0x%08llx", val);

	return trace_seq_printf(s, fmt, tmp);

 failed:
	if (err)
		trace_seq_printf(s, "CAN'T FIND FIELD \"%s\"", name);
	return -1;
}