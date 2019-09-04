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
typedef  int /*<<< orphan*/ * tep_event_handler_func ;
struct tep_handle {struct event_handler* handlers; } ;
struct event_handler {struct event_handler* next; } ;
struct event_format {void* context; int /*<<< orphan*/ * handler; int /*<<< orphan*/  name; int /*<<< orphan*/  system; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_handler (struct event_handler*) ; 
 scalar_t__ handle_matches (struct event_handler*,int,char const*,char const*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  pr_stat (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct event_format* search_event (struct tep_handle*,int,char const*,char const*) ; 

int tep_unregister_event_handler(struct tep_handle *pevent, int id,
				 const char *sys_name, const char *event_name,
				 tep_event_handler_func func, void *context)
{
	struct event_format *event;
	struct event_handler *handle;
	struct event_handler **next;

	event = search_event(pevent, id, sys_name, event_name);
	if (event == NULL)
		goto not_found;

	if (event->handler == func && event->context == context) {
		pr_stat("removing override handler for event (%d) %s:%s. Going back to default handler.",
			event->id, event->system, event->name);

		event->handler = NULL;
		event->context = NULL;
		return 0;
	}

not_found:
	for (next = &pevent->handlers; *next; next = &(*next)->next) {
		handle = *next;
		if (handle_matches(handle, id, sys_name, event_name,
				   func, context))
			break;
	}

	if (!(*next))
		return -1;

	*next = handle->next;
	free_handler(handle);

	return 0;
}