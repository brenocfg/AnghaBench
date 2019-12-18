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
struct devlink_info_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_INFO_VERSION_STORED ; 
 int devlink_info_version_put (struct devlink_info_req*,int /*<<< orphan*/ ,char const*,char const*) ; 

int devlink_info_version_stored_put(struct devlink_info_req *req,
				    const char *version_name,
				    const char *version_value)
{
	return devlink_info_version_put(req, DEVLINK_ATTR_INFO_VERSION_STORED,
					version_name, version_value);
}