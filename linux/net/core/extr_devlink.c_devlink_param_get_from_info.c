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
struct list_head {int dummy; } ;
struct genl_info {int /*<<< orphan*/ * attrs; } ;
struct devlink_param_item {int dummy; } ;

/* Variables and functions */
 size_t DEVLINK_ATTR_PARAM_NAME ; 
 struct devlink_param_item* devlink_param_find_by_name (struct list_head*,char*) ; 
 char* nla_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct devlink_param_item *
devlink_param_get_from_info(struct list_head *param_list,
			    struct genl_info *info)
{
	char *param_name;

	if (!info->attrs[DEVLINK_ATTR_PARAM_NAME])
		return NULL;

	param_name = nla_data(info->attrs[DEVLINK_ATTR_PARAM_NAME]);
	return devlink_param_find_by_name(param_list, param_name);
}