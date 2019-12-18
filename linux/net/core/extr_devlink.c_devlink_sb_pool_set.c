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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct netlink_ext_ack {int dummy; } ;
struct devlink_ops {int (* sb_pool_set ) (struct devlink*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct netlink_ext_ack*) ;} ;
struct devlink {struct devlink_ops* ops; } ;
typedef  enum devlink_sb_threshold_type { ____Placeholder_devlink_sb_threshold_type } devlink_sb_threshold_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct devlink*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct netlink_ext_ack*) ; 

__attribute__((used)) static int devlink_sb_pool_set(struct devlink *devlink, unsigned int sb_index,
			       u16 pool_index, u32 size,
			       enum devlink_sb_threshold_type threshold_type,
			       struct netlink_ext_ack *extack)

{
	const struct devlink_ops *ops = devlink->ops;

	if (ops->sb_pool_set)
		return ops->sb_pool_set(devlink, sb_index, pool_index,
					size, threshold_type, extack);
	return -EOPNOTSUPP;
}