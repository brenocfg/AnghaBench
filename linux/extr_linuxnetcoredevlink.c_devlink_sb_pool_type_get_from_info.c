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
struct genl_info {int /*<<< orphan*/  attrs; } ;
typedef  enum devlink_sb_pool_type { ____Placeholder_devlink_sb_pool_type } devlink_sb_pool_type ;

/* Variables and functions */
 int devlink_sb_pool_type_get_from_attrs (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
devlink_sb_pool_type_get_from_info(struct genl_info *info,
				   enum devlink_sb_pool_type *p_pool_type)
{
	return devlink_sb_pool_type_get_from_attrs(info->attrs, p_pool_type);
}