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
struct tep_format_field {int offset; int size; int /*<<< orphan*/  type; } ;
struct tep_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 struct tep_format_field* tep_find_field (struct tep_event*,char const*) ; 
 scalar_t__ tep_read_number_field (struct tep_format_field*,void const*,unsigned long long*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,...) ; 

__attribute__((used)) static void print_string(struct trace_seq *s, struct tep_event *event,
			 const char *name, const void *data)
{
	struct tep_format_field *f = tep_find_field(event, name);
	int offset;
	int length;

	if (!f) {
		trace_seq_printf(s, "NOTFOUND:%s", name);
		return;
	}

	offset = f->offset;
	length = f->size;

	if (!strncmp(f->type, "__data_loc", 10)) {
		unsigned long long v;
		if (tep_read_number_field(f, data, &v)) {
			trace_seq_printf(s, "invalid_data_loc");
			return;
		}
		offset = v & 0xffff;
		length = v >> 16;
	}

	trace_seq_printf(s, "%.*s", length, (char *)data + offset);
}