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
struct devlink {int reload_failed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_CMD_NEW ; 
 int /*<<< orphan*/  devlink_notify (struct devlink*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void devlink_reload_failed_set(struct devlink *devlink,
				      bool reload_failed)
{
	if (devlink->reload_failed == reload_failed)
		return;
	devlink->reload_failed = reload_failed;
	devlink_notify(devlink, DEVLINK_CMD_NEW);
}