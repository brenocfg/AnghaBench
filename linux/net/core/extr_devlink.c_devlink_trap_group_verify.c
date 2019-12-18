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
struct devlink_trap_group {scalar_t__ generic; } ;

/* Variables and functions */
 int devlink_trap_group_driver_verify (struct devlink_trap_group const*) ; 
 int devlink_trap_group_generic_verify (struct devlink_trap_group const*) ; 

__attribute__((used)) static int devlink_trap_group_verify(const struct devlink_trap_group *group)
{
	if (group->generic)
		return devlink_trap_group_generic_verify(group);
	else
		return devlink_trap_group_driver_verify(group);
}