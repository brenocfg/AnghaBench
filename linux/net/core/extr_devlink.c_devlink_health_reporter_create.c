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
typedef  scalar_t__ u64 ;
struct devlink_health_reporter_ops {int /*<<< orphan*/  recover; int /*<<< orphan*/  name; } ;
struct devlink_health_reporter {int auto_recover; int /*<<< orphan*/  list; int /*<<< orphan*/  refcount; int /*<<< orphan*/  dump_lock; scalar_t__ graceful_period; struct devlink* devlink; struct devlink_health_reporter_ops const* ops; void* priv; } ;
struct devlink {int /*<<< orphan*/  reporters_lock; int /*<<< orphan*/  reporter_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct devlink_health_reporter* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ devlink_health_reporter_find_by_name (struct devlink*,int /*<<< orphan*/ ) ; 
 struct devlink_health_reporter* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

struct devlink_health_reporter *
devlink_health_reporter_create(struct devlink *devlink,
			       const struct devlink_health_reporter_ops *ops,
			       u64 graceful_period, bool auto_recover,
			       void *priv)
{
	struct devlink_health_reporter *reporter;

	mutex_lock(&devlink->reporters_lock);
	if (devlink_health_reporter_find_by_name(devlink, ops->name)) {
		reporter = ERR_PTR(-EEXIST);
		goto unlock;
	}

	if (WARN_ON(auto_recover && !ops->recover) ||
	    WARN_ON(graceful_period && !ops->recover)) {
		reporter = ERR_PTR(-EINVAL);
		goto unlock;
	}

	reporter = kzalloc(sizeof(*reporter), GFP_KERNEL);
	if (!reporter) {
		reporter = ERR_PTR(-ENOMEM);
		goto unlock;
	}

	reporter->priv = priv;
	reporter->ops = ops;
	reporter->devlink = devlink;
	reporter->graceful_period = graceful_period;
	reporter->auto_recover = auto_recover;
	mutex_init(&reporter->dump_lock);
	refcount_set(&reporter->refcount, 1);
	list_add_tail(&reporter->list, &devlink->reporter_list);
unlock:
	mutex_unlock(&devlink->reporters_lock);
	return reporter;
}