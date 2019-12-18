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
struct tep_format_field {int dummy; } ;
struct evsel {TYPE_2__* tp_format; } ;
struct ctf_writer {int dummy; } ;
struct bt_ctf_event_class {int dummy; } ;
struct TYPE_3__ {struct tep_format_field* fields; struct tep_format_field* common_fields; } ;
struct TYPE_4__ {TYPE_1__ format; } ;

/* Variables and functions */
 int add_tracepoint_fields_types (struct ctf_writer*,struct tep_format_field*,struct bt_ctf_event_class*) ; 

__attribute__((used)) static int add_tracepoint_types(struct ctf_writer *cw,
				struct evsel *evsel,
				struct bt_ctf_event_class *class)
{
	struct tep_format_field *common_fields = evsel->tp_format->format.common_fields;
	struct tep_format_field *fields        = evsel->tp_format->format.fields;
	int ret;

	ret = add_tracepoint_fields_types(cw, common_fields, class);
	if (!ret)
		ret = add_tracepoint_fields_types(cw, fields, class);

	return ret;
}