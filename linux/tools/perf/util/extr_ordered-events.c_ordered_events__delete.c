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
struct ordered_events {int /*<<< orphan*/  nr_events; int /*<<< orphan*/  cache; } ;
struct ordered_event {int /*<<< orphan*/ * event; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_dup_event (struct ordered_events*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ordered_events__delete(struct ordered_events *oe, struct ordered_event *event)
{
	list_move(&event->list, &oe->cache);
	oe->nr_events--;
	free_dup_event(oe, event->event);
	event->event = NULL;
}