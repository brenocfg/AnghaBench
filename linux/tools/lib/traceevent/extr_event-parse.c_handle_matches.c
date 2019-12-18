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
typedef  scalar_t__ tep_event_handler_func ;
struct event_handler {int id; scalar_t__ func; void* context; int /*<<< orphan*/  sys_name; int /*<<< orphan*/  event_name; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_matches(struct event_handler *handler, int id,
			  const char *sys_name, const char *event_name,
			  tep_event_handler_func func, void *context)
{
	if (id >= 0 && id != handler->id)
		return 0;

	if (event_name && (strcmp(event_name, handler->event_name) != 0))
		return 0;

	if (sys_name && (strcmp(sys_name, handler->sys_name) != 0))
		return 0;

	if (func != handler->func || context != handler->context)
		return 0;

	return 1;
}