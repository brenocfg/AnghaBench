#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct devlink_trap {size_t id; scalar_t__ type; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 size_t DEVLINK_TRAP_GENERIC_ID_MAX ; 
 int EINVAL ; 
 TYPE_1__* devlink_trap_generic ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_trap_generic_verify(const struct devlink_trap *trap)
{
	if (trap->id > DEVLINK_TRAP_GENERIC_ID_MAX)
		return -EINVAL;

	if (strcmp(trap->name, devlink_trap_generic[trap->id].name))
		return -EINVAL;

	if (trap->type != devlink_trap_generic[trap->id].type)
		return -EINVAL;

	return 0;
}