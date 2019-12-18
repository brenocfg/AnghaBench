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
struct tep_filter_type {struct tep_filter_arg* filter; TYPE_1__* event; } ;
struct TYPE_4__ {int value; } ;
struct tep_filter_arg {TYPE_2__ boolean; int /*<<< orphan*/  type; } ;
struct tep_event_filter {int /*<<< orphan*/  tep; } ;
struct tep_event {int /*<<< orphan*/  id; } ;
struct TYPE_3__ {char* system; char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEP_FILTER_ARG_BOOLEAN ; 
 struct tep_filter_type* add_filter_type (struct tep_event_filter*,int /*<<< orphan*/ ) ; 
 struct tep_filter_arg* allocate_arg () ; 
 char* arg_to_str (struct tep_event_filter*,struct tep_filter_arg*) ; 
 int /*<<< orphan*/  filter_event (struct tep_event_filter*,struct tep_event*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 struct tep_event* tep_find_event_by_name (int /*<<< orphan*/ ,char const*,char const*) ; 

__attribute__((used)) static int copy_filter_type(struct tep_event_filter *filter,
			    struct tep_event_filter *source,
			    struct tep_filter_type *filter_type)
{
	struct tep_filter_arg *arg;
	struct tep_event *event;
	const char *sys;
	const char *name;
	char *str;

	/* Can't assume that the tep's are the same */
	sys = filter_type->event->system;
	name = filter_type->event->name;
	event = tep_find_event_by_name(filter->tep, sys, name);
	if (!event)
		return -1;

	str = arg_to_str(source, filter_type->filter);
	if (!str)
		return -1;

	if (strcmp(str, "TRUE") == 0 || strcmp(str, "FALSE") == 0) {
		/* Add trivial event */
		arg = allocate_arg();
		if (arg == NULL)
			return -1;

		arg->type = TEP_FILTER_ARG_BOOLEAN;
		if (strcmp(str, "TRUE") == 0)
			arg->boolean.value = 1;
		else
			arg->boolean.value = 0;

		filter_type = add_filter_type(filter, event->id);
		if (filter_type == NULL)
			return -1;

		filter_type->filter = arg;

		free(str);
		return 0;
	}

	filter_event(filter, event, str, NULL);
	free(str);

	return 0;
}