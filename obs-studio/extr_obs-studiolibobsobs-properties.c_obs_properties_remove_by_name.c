#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct obs_property {struct obs_property* next; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {struct obs_property* first_property; } ;
typedef  TYPE_1__ obs_properties_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_property_destroy (struct obs_property*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

void obs_properties_remove_by_name(obs_properties_t *props, const char *name)
{
	if (!props)
		return;

	/* obs_properties_t is a forward-linked-list, so we need to keep both
	 * previous and current pointers around. That way we can fix up the
	 * pointers for the previous element if we find a match.
	 */
	struct obs_property *cur = props->first_property;
	struct obs_property *prev = props->first_property;

	while (cur) {
		if (strcmp(cur->name, name) == 0) {
			prev->next = cur->next;
			cur->next = 0;
			obs_property_destroy(cur);
			break;
		}

		prev = cur;
		cur = cur->next;
	}
}