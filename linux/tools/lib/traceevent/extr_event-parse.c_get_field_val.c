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
struct tep_format_field {int dummy; } ;

/* Variables and functions */
 scalar_t__ tep_read_number_field (struct tep_format_field*,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,char const*) ; 

int get_field_val(struct trace_seq *s, struct tep_format_field *field,
		  const char *name, struct tep_record *record,
		  unsigned long long *val, int err)
{
	if (!field) {
		if (err)
			trace_seq_printf(s, "<CANT FIND FIELD %s>", name);
		return -1;
	}

	if (tep_read_number_field(field, record->data, val)) {
		if (err)
			trace_seq_printf(s, " %s=INVALID", name);
		return -1;
	}

	return 0;
}