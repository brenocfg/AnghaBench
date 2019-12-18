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
struct devlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_CMD_FLASH_UPDATE_STATUS ; 
 int /*<<< orphan*/  __devlink_flash_update_notify (struct devlink*,int /*<<< orphan*/ ,char const*,char const*,unsigned long,unsigned long) ; 

void devlink_flash_update_status_notify(struct devlink *devlink,
					const char *status_msg,
					const char *component,
					unsigned long done,
					unsigned long total)
{
	__devlink_flash_update_notify(devlink,
				      DEVLINK_CMD_FLASH_UPDATE_STATUS,
				      status_msg, component, done, total);
}