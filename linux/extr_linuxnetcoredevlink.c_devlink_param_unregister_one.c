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
struct devlink_param_item {int /*<<< orphan*/  list; } ;
struct devlink_param {int /*<<< orphan*/  name; } ;
struct devlink {int /*<<< orphan*/  param_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_CMD_PARAM_DEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct devlink_param_item* devlink_param_find_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_param_notify (struct devlink*,struct devlink_param_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct devlink_param_item*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void devlink_param_unregister_one(struct devlink *devlink,
					 const struct devlink_param *param)
{
	struct devlink_param_item *param_item;

	param_item = devlink_param_find_by_name(&devlink->param_list,
						param->name);
	WARN_ON(!param_item);
	devlink_param_notify(devlink, param_item, DEVLINK_CMD_PARAM_DEL);
	list_del(&param_item->list);
	kfree(param_item);
}