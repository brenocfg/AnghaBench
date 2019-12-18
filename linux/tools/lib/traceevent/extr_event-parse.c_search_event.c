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
struct tep_handle {int dummy; } ;
struct tep_event {int /*<<< orphan*/  system; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 struct tep_event* tep_find_event (struct tep_handle*,int) ; 
 struct tep_event* tep_find_event_by_name (struct tep_handle*,char const*,char const*) ; 

__attribute__((used)) static struct tep_event *search_event(struct tep_handle *tep, int id,
				      const char *sys_name,
				      const char *event_name)
{
	struct tep_event *event;

	if (id >= 0) {
		/* search by id */
		event = tep_find_event(tep, id);
		if (!event)
			return NULL;
		if (event_name && (strcmp(event_name, event->name) != 0))
			return NULL;
		if (sys_name && (strcmp(sys_name, event->system) != 0))
			return NULL;
	} else {
		event = tep_find_event_by_name(tep, sys_name, event_name);
		if (!event)
			return NULL;
	}
	return event;
}