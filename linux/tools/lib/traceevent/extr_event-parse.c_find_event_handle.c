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
struct tep_handle {struct event_handler* handlers; } ;
struct tep_event {int /*<<< orphan*/  context; int /*<<< orphan*/  handler; int /*<<< orphan*/  name; int /*<<< orphan*/  system; int /*<<< orphan*/  id; } ;
struct event_handler {struct event_handler* next; int /*<<< orphan*/  context; int /*<<< orphan*/  func; int /*<<< orphan*/  event_name; int /*<<< orphan*/  sys_name; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ event_matches (struct tep_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_handler (struct event_handler*) ; 
 int /*<<< orphan*/  pr_stat (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_event_handle(struct tep_handle *tep, struct tep_event *event)
{
	struct event_handler *handle, **next;

	for (next = &tep->handlers; *next;
	     next = &(*next)->next) {
		handle = *next;
		if (event_matches(event, handle->id,
				  handle->sys_name,
				  handle->event_name))
			break;
	}

	if (!(*next))
		return 0;

	pr_stat("overriding event (%d) %s:%s with new print handler",
		event->id, event->system, event->name);

	event->handler = handle->func;
	event->context = handle->context;

	*next = handle->next;
	free_handler(handle);

	return 1;
}