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
struct tep_event {int id; int /*<<< orphan*/  system; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int event_matches(struct tep_event *event,
			 int id, const char *sys_name,
			 const char *event_name)
{
	if (id >= 0 && id != event->id)
		return 0;

	if (event_name && (strcmp(event_name, event->name) != 0))
		return 0;

	if (sys_name && (strcmp(sys_name, event->system) != 0))
		return 0;

	return 1;
}