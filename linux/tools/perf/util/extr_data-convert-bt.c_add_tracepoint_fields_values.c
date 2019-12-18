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
struct tep_format_field {struct tep_format_field* next; } ;
struct perf_sample {int dummy; } ;
struct ctf_writer {int dummy; } ;
struct bt_ctf_event_class {int dummy; } ;
struct bt_ctf_event {int dummy; } ;

/* Variables and functions */
 int add_tracepoint_field_value (struct ctf_writer*,struct bt_ctf_event_class*,struct bt_ctf_event*,struct perf_sample*,struct tep_format_field*) ; 

__attribute__((used)) static int add_tracepoint_fields_values(struct ctf_writer *cw,
					struct bt_ctf_event_class *event_class,
					struct bt_ctf_event *event,
					struct tep_format_field *fields,
					struct perf_sample *sample)
{
	struct tep_format_field *field;
	int ret;

	for (field = fields; field; field = field->next) {
		ret = add_tracepoint_field_value(cw, event_class, event, sample,
				field);
		if (ret)
			return -1;
	}
	return 0;
}