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
typedef  scalar_t__ u16 ;
struct nlattr {int dummy; } ;
struct devlink_sb {scalar_t__ ingress_tc_count; scalar_t__ egress_tc_count; } ;
typedef  enum devlink_sb_pool_type { ____Placeholder_devlink_sb_pool_type } devlink_sb_pool_type ;

/* Variables and functions */
 size_t DEVLINK_ATTR_SB_TC_INDEX ; 
 int DEVLINK_SB_POOL_TYPE_EGRESS ; 
 int DEVLINK_SB_POOL_TYPE_INGRESS ; 
 int EINVAL ; 
 scalar_t__ nla_get_u16 (struct nlattr*) ; 

__attribute__((used)) static int
devlink_sb_tc_index_get_from_attrs(struct devlink_sb *devlink_sb,
				   struct nlattr **attrs,
				   enum devlink_sb_pool_type pool_type,
				   u16 *p_tc_index)
{
	u16 val;

	if (!attrs[DEVLINK_ATTR_SB_TC_INDEX])
		return -EINVAL;

	val = nla_get_u16(attrs[DEVLINK_ATTR_SB_TC_INDEX]);
	if (pool_type == DEVLINK_SB_POOL_TYPE_INGRESS &&
	    val >= devlink_sb->ingress_tc_count)
		return -EINVAL;
	if (pool_type == DEVLINK_SB_POOL_TYPE_EGRESS &&
	    val >= devlink_sb->egress_tc_count)
		return -EINVAL;
	*p_tc_index = val;
	return 0;
}