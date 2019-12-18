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
struct genl_info {struct devlink_sb** user_ptr; } ;
struct devlink_sb {int /*<<< orphan*/  index; struct devlink_ops* ops; } ;
struct devlink_ops {int (* sb_occ_snapshot ) (struct devlink_sb*,int /*<<< orphan*/ ) ;} ;
struct devlink {int /*<<< orphan*/  index; struct devlink_ops* ops; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct devlink_sb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_nl_cmd_sb_occ_snapshot_doit(struct sk_buff *skb,
					       struct genl_info *info)
{
	struct devlink *devlink = info->user_ptr[0];
	struct devlink_sb *devlink_sb = info->user_ptr[1];
	const struct devlink_ops *ops = devlink->ops;

	if (ops->sb_occ_snapshot)
		return ops->sb_occ_snapshot(devlink, devlink_sb->index);
	return -EOPNOTSUPP;
}