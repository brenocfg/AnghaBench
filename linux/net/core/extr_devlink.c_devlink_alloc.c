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
struct devlink_ops {int dummy; } ;
struct devlink {int /*<<< orphan*/  reporters_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  trap_group_list; int /*<<< orphan*/  trap_list; int /*<<< orphan*/  reporter_list; int /*<<< orphan*/  region_list; int /*<<< orphan*/  param_list; int /*<<< orphan*/  resource_list; int /*<<< orphan*/  dpipe_table_list; int /*<<< orphan*/  sb_list; int /*<<< orphan*/  port_list; struct devlink_ops const* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD_RCU (int /*<<< orphan*/ *) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  devlink_net_set (struct devlink*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_net ; 
 struct devlink* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct devlink *devlink_alloc(const struct devlink_ops *ops, size_t priv_size)
{
	struct devlink *devlink;

	if (WARN_ON(!ops))
		return NULL;

	devlink = kzalloc(sizeof(*devlink) + priv_size, GFP_KERNEL);
	if (!devlink)
		return NULL;
	devlink->ops = ops;
	devlink_net_set(devlink, &init_net);
	INIT_LIST_HEAD(&devlink->port_list);
	INIT_LIST_HEAD(&devlink->sb_list);
	INIT_LIST_HEAD_RCU(&devlink->dpipe_table_list);
	INIT_LIST_HEAD(&devlink->resource_list);
	INIT_LIST_HEAD(&devlink->param_list);
	INIT_LIST_HEAD(&devlink->region_list);
	INIT_LIST_HEAD(&devlink->reporter_list);
	INIT_LIST_HEAD(&devlink->trap_list);
	INIT_LIST_HEAD(&devlink->trap_group_list);
	mutex_init(&devlink->lock);
	mutex_init(&devlink->reporters_lock);
	return devlink;
}