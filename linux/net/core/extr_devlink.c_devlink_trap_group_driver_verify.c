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
struct devlink_trap_group {scalar_t__ id; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ DEVLINK_TRAP_GROUP_GENERIC_ID_MAX ; 
 int EEXIST ; 
 int EINVAL ; 
 TYPE_1__* devlink_trap_group_generic ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
devlink_trap_group_driver_verify(const struct devlink_trap_group *group)
{
	int i;

	if (group->id <= DEVLINK_TRAP_GROUP_GENERIC_ID_MAX)
		return -EINVAL;

	for (i = 0; i < ARRAY_SIZE(devlink_trap_group_generic); i++) {
		if (!strcmp(group->name, devlink_trap_group_generic[i].name))
			return -EEXIST;
	}

	return 0;
}