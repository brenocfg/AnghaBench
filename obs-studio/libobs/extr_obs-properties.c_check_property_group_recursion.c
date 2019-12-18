#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ type; struct TYPE_7__* next; } ;
typedef  TYPE_1__ obs_property_t ;
struct TYPE_8__ {TYPE_1__* first_property; } ;
typedef  TYPE_2__ obs_properties_t ;

/* Variables and functions */
 scalar_t__ OBS_PROPERTY_GROUP ; 
 TYPE_2__* obs_property_group_content (TYPE_1__*) ; 

__attribute__((used)) static bool check_property_group_recursion(obs_properties_t *parent,
					   obs_properties_t *group)
{
	/* Scan the group for the parent. */
	obs_property_t *current_property = group->first_property;
	while (current_property) {
		if (current_property->type == OBS_PROPERTY_GROUP) {
			obs_properties_t *cprops =
				obs_property_group_content(current_property);
			if (cprops == parent) {
				/* Contains find_props */
				return true;
			} else if (cprops == group) {
				/* Contains self, shouldn't be possible but
				 * lets verify anyway. */
				return true;
			}
			check_property_group_recursion(cprops, group);
		}

		current_property = current_property->next;
	}

	return false;
}