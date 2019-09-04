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
struct genl_info {int dummy; } ;
struct devlink {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int DEVLINK_NL_FLAG_NO_LOCK ; 
 struct devlink* devlink_get_from_info (struct genl_info*) ; 
 int /*<<< orphan*/  devlink_mutex ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void devlink_nl_post_doit(const struct genl_ops *ops,
				 struct sk_buff *skb, struct genl_info *info)
{
	struct devlink *devlink;

	devlink = devlink_get_from_info(info);
	if (~ops->internal_flags & DEVLINK_NL_FLAG_NO_LOCK)
		mutex_unlock(&devlink->lock);
	mutex_unlock(&devlink_mutex);
}