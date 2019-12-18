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
struct genl_info {int /*<<< orphan*/  attrs; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 struct devlink* devlink_get_from_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genl_info_net (struct genl_info*) ; 

__attribute__((used)) static struct devlink *devlink_get_from_info(struct genl_info *info)
{
	return devlink_get_from_attrs(genl_info_net(info), info->attrs);
}