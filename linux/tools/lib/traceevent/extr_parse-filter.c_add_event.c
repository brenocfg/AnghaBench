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
struct tep_event {int dummy; } ;
struct event_list {struct tep_event* event; struct event_list* next; } ;

/* Variables and functions */
 struct event_list* malloc (int) ; 

__attribute__((used)) static int add_event(struct event_list **events,
		     struct tep_event *event)
{
	struct event_list *list;

	list = malloc(sizeof(*list));
	if (list == NULL)
		return -1;

	list->next = *events;
	*events = list;
	list->event = event;
	return 0;
}