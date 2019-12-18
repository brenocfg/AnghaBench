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
struct devlink_param_item {int /*<<< orphan*/  list; } ;
struct devlink_param {int /*<<< orphan*/  name; } ;
struct devlink {int dummy; } ;
typedef  enum devlink_command { ____Placeholder_devlink_command } devlink_command ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct devlink_param_item* devlink_param_find_by_name (struct list_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_param_notify (struct devlink*,unsigned int,struct devlink_param_item*,int) ; 
 int /*<<< orphan*/  kfree (struct devlink_param_item*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void devlink_param_unregister_one(struct devlink *devlink,
					 unsigned int port_index,
					 struct list_head *param_list,
					 const struct devlink_param *param,
					 enum devlink_command cmd)
{
	struct devlink_param_item *param_item;

	param_item = devlink_param_find_by_name(param_list, param->name);
	WARN_ON(!param_item);
	devlink_param_notify(devlink, port_index, param_item, cmd);
	list_del(&param_item->list);
	kfree(param_item);
}