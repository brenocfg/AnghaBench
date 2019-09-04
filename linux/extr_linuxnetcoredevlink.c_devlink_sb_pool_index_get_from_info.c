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
typedef  int /*<<< orphan*/  u16 ;
struct genl_info {int /*<<< orphan*/  attrs; } ;
struct devlink_sb {int dummy; } ;

/* Variables and functions */
 int devlink_sb_pool_index_get_from_attrs (struct devlink_sb*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int devlink_sb_pool_index_get_from_info(struct devlink_sb *devlink_sb,
					       struct genl_info *info,
					       u16 *p_pool_index)
{
	return devlink_sb_pool_index_get_from_attrs(devlink_sb, info->attrs,
						    p_pool_index);
}