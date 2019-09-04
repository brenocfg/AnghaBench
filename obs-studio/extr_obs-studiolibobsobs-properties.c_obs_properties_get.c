#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct obs_property {scalar_t__ type; struct obs_property* next; int /*<<< orphan*/  name; } ;
typedef  struct obs_property obs_property_t ;
struct TYPE_4__ {struct obs_property* first_property; } ;
typedef  TYPE_1__ obs_properties_t ;

/* Variables and functions */
 scalar_t__ OBS_PROPERTY_GROUP ; 
 TYPE_1__* obs_property_group_content (struct obs_property*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

obs_property_t *obs_properties_get(obs_properties_t *props, const char *name)
{
	struct obs_property *property;

	if (!props)
		return NULL;

	property = props->first_property;
	while (property) {
		if (strcmp(property->name, name) == 0)
			return property;

		if (property->type == OBS_PROPERTY_GROUP) {
			obs_properties_t *group =
				obs_property_group_content(property);
			obs_property_t *found = obs_properties_get(group, name);
			if (found != NULL) {
				return found;
			}
		}

		property = property->next;
	}

	return NULL;
}