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
struct sk_buff {int dummy; } ;
struct genl_ops {int internal_flags; } ;
struct genl_info {struct devlink_sb** user_ptr; } ;
struct devlink_sb {int /*<<< orphan*/  lock; } ;
struct devlink_port {int /*<<< orphan*/  lock; } ;
struct devlink {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int DEVLINK_NL_FLAG_NEED_DEVLINK ; 
 int DEVLINK_NL_FLAG_NEED_PORT ; 
 int DEVLINK_NL_FLAG_NEED_SB ; 
 int DEVLINK_NL_FLAG_NO_LOCK ; 
 scalar_t__ IS_ERR (struct devlink_sb*) ; 
 int PTR_ERR (struct devlink_sb*) ; 
 struct devlink_sb* devlink_get_from_info (struct genl_info*) ; 
 int /*<<< orphan*/  devlink_mutex ; 
 struct devlink_sb* devlink_port_get_from_info (struct devlink_sb*,struct genl_info*) ; 
 struct devlink_sb* devlink_sb_get_from_info (struct devlink_sb*,struct genl_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int devlink_nl_pre_doit(const struct genl_ops *ops,
			       struct sk_buff *skb, struct genl_info *info)
{
	struct devlink *devlink;
	int err;

	mutex_lock(&devlink_mutex);
	devlink = devlink_get_from_info(info);
	if (IS_ERR(devlink)) {
		mutex_unlock(&devlink_mutex);
		return PTR_ERR(devlink);
	}
	if (~ops->internal_flags & DEVLINK_NL_FLAG_NO_LOCK)
		mutex_lock(&devlink->lock);
	if (ops->internal_flags & DEVLINK_NL_FLAG_NEED_DEVLINK) {
		info->user_ptr[0] = devlink;
	} else if (ops->internal_flags & DEVLINK_NL_FLAG_NEED_PORT) {
		struct devlink_port *devlink_port;

		devlink_port = devlink_port_get_from_info(devlink, info);
		if (IS_ERR(devlink_port)) {
			err = PTR_ERR(devlink_port);
			goto unlock;
		}
		info->user_ptr[0] = devlink_port;
	}
	if (ops->internal_flags & DEVLINK_NL_FLAG_NEED_SB) {
		struct devlink_sb *devlink_sb;

		devlink_sb = devlink_sb_get_from_info(devlink, info);
		if (IS_ERR(devlink_sb)) {
			err = PTR_ERR(devlink_sb);
			goto unlock;
		}
		info->user_ptr[1] = devlink_sb;
	}
	return 0;

unlock:
	if (~ops->internal_flags & DEVLINK_NL_FLAG_NO_LOCK)
		mutex_unlock(&devlink->lock);
	mutex_unlock(&devlink_mutex);
	return err;
}