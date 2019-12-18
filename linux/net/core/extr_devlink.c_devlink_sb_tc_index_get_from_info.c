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
typedef  enum devlink_sb_pool_type { ____Placeholder_devlink_sb_pool_type } devlink_sb_pool_type ;

/* Variables and functions */
 int devlink_sb_tc_index_get_from_attrs (struct devlink_sb*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
devlink_sb_tc_index_get_from_info(struct devlink_sb *devlink_sb,
				  struct genl_info *info,
				  enum devlink_sb_pool_type pool_type,
				  u16 *p_tc_index)
{
	return devlink_sb_tc_index_get_from_attrs(devlink_sb, info->attrs,
						  pool_type, p_tc_index);
}