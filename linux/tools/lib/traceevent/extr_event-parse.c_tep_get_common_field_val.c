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
struct tep_format_field {int dummy; } ;
struct tep_event {int dummy; } ;

/* Variables and functions */
 int get_field_val (struct trace_seq*,struct tep_format_field*,char const*,struct tep_record*,unsigned long long*,int) ; 
 struct tep_format_field* tep_find_common_field (struct tep_event*,char const*) ; 

int tep_get_common_field_val(struct trace_seq *s, struct tep_event *event,
			     const char *name, struct tep_record *record,
			     unsigned long long *val, int err)
{
	struct tep_format_field *field;

	if (!event)
		return -1;

	field = tep_find_common_field(event, name);

	return get_field_val(s, field, name, record, val, err);
}