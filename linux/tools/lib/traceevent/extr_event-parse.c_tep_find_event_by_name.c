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
struct tep_handle {int nr_events; struct tep_event* last_event; struct tep_event** events; } ;
struct tep_event {int /*<<< orphan*/  system; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

struct tep_event *
tep_find_event_by_name(struct tep_handle *tep,
		       const char *sys, const char *name)
{
	struct tep_event *event = NULL;
	int i;

	if (tep->last_event &&
	    strcmp(tep->last_event->name, name) == 0 &&
	    (!sys || strcmp(tep->last_event->system, sys) == 0))
		return tep->last_event;

	for (i = 0; i < tep->nr_events; i++) {
		event = tep->events[i];
		if (strcmp(event->name, name) == 0) {
			if (!sys)
				break;
			if (strcmp(event->system, sys) == 0)
				break;
		}
	}
	if (i == tep->nr_events)
		event = NULL;

	tep->last_event = event;
	return event;
}