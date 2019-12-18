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
struct tep_format_field {struct tep_format_field* next; } ;
struct evsel {TYPE_2__* tp_format; } ;
struct TYPE_3__ {struct tep_format_field* fields; } ;
struct TYPE_4__ {TYPE_1__ format; } ;

/* Variables and functions */
 int __dynamic_dimension__add (struct evsel*,struct tep_format_field*,int,int) ; 

__attribute__((used)) static int add_evsel_fields(struct evsel *evsel, bool raw_trace, int level)
{
	int ret;
	struct tep_format_field *field;

	field = evsel->tp_format->format.fields;
	while (field) {
		ret = __dynamic_dimension__add(evsel, field, raw_trace, level);
		if (ret < 0)
			return ret;

		field = field->next;
	}
	return 0;
}