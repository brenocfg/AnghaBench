#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct synth_event {int n_fields; TYPE_1__** fields; } ;
struct TYPE_2__ {char* name; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEN_OR_ZERO ; 
 scalar_t__ snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 char* synth_field_fmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __set_synth_event_print_fmt(struct synth_event *event,
				       char *buf, int len)
{
	const char *fmt;
	int pos = 0;
	int i;

	/* When len=0, we just calculate the needed length */
#define LEN_OR_ZERO (len ? len - pos : 0)

	pos += snprintf(buf + pos, LEN_OR_ZERO, "\"");
	for (i = 0; i < event->n_fields; i++) {
		fmt = synth_field_fmt(event->fields[i]->type);
		pos += snprintf(buf + pos, LEN_OR_ZERO, "%s=%s%s",
				event->fields[i]->name, fmt,
				i == event->n_fields - 1 ? "" : ", ");
	}
	pos += snprintf(buf + pos, LEN_OR_ZERO, "\"");

	for (i = 0; i < event->n_fields; i++) {
		pos += snprintf(buf + pos, LEN_OR_ZERO,
				", REC->%s", event->fields[i]->name);
	}

#undef LEN_OR_ZERO

	/* return the length of print_fmt */
	return pos;
}