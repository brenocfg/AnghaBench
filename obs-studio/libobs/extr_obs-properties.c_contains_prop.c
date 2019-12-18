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
struct obs_property {scalar_t__ type; struct obs_property* next; int /*<<< orphan*/  name; } ;
struct obs_properties {struct obs_property* first_property; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ OBS_PROPERTY_GROUP ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char const*) ; 
 struct obs_properties* obs_property_group_content (struct obs_property*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static inline bool contains_prop(struct obs_properties *props, const char *name)
{
	struct obs_property *p = props->first_property;

	while (p) {
		if (strcmp(p->name, name) == 0) {
			blog(LOG_WARNING, "Property '%s' exists", name);
			return true;
		}

		if (p->type == OBS_PROPERTY_GROUP) {
			if (contains_prop(obs_property_group_content(p),
					  name)) {
				return true;
			}
		}

		p = p->next;
	}

	return false;
}