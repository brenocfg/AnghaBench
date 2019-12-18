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
struct tep_handle {int last_type; int /*<<< orphan*/  nr_events; struct tep_event** sort_events; } ;
struct tep_event {int dummy; } ;
typedef  enum tep_event_sort_type { ____Placeholder_tep_event_sort_type } tep_event_sort_type ;

/* Variables and functions */
 int TEP_EVENT_SORT_ID ; 
 struct tep_event** list_events_copy (struct tep_handle*) ; 
 int /*<<< orphan*/  list_events_sort (struct tep_event**,int /*<<< orphan*/ ,int) ; 

struct tep_event **tep_list_events(struct tep_handle *tep,
				   enum tep_event_sort_type sort_type)
{
	struct tep_event **events;

	if (!tep)
		return NULL;

	events = tep->sort_events;
	if (events && tep->last_type == sort_type)
		return events;

	if (!events) {
		events = list_events_copy(tep);
		if (!events)
			return NULL;

		tep->sort_events = events;

		/* the internal events are sorted by id */
		if (sort_type == TEP_EVENT_SORT_ID) {
			tep->last_type = sort_type;
			return events;
		}
	}

	list_events_sort(events, tep->nr_events, sort_type);
	tep->last_type = sort_type;

	return events;
}