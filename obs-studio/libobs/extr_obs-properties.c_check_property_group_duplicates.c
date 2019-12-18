#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ obs_property_t ;
struct TYPE_7__ {TYPE_1__* first_property; } ;
typedef  TYPE_2__ obs_properties_t ;

/* Variables and functions */
 scalar_t__ has_prop (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool check_property_group_duplicates(obs_properties_t *parent,
					    obs_properties_t *group)
{
	obs_property_t *current_property = group->first_property;
	while (current_property) {
		if (has_prop(parent, current_property->name)) {
			return true;
		}

		current_property = current_property->next;
	}

	return false;
}