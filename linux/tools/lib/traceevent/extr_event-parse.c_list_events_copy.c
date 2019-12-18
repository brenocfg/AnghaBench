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
struct tep_handle {int nr_events; int /*<<< orphan*/  events; } ;
struct tep_event {int dummy; } ;

/* Variables and functions */
 struct tep_event** malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct tep_event**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct tep_event **list_events_copy(struct tep_handle *tep)
{
	struct tep_event **events;

	if (!tep)
		return NULL;

	events = malloc(sizeof(*events) * (tep->nr_events + 1));
	if (!events)
		return NULL;

	memcpy(events, tep->events, sizeof(*events) * tep->nr_events);
	events[tep->nr_events] = NULL;
	return events;
}