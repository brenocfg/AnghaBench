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
typedef  scalar_t__ u8 ;
struct nlattr {int dummy; } ;
typedef  enum devlink_sb_pool_type { ____Placeholder_devlink_sb_pool_type } devlink_sb_pool_type ;

/* Variables and functions */
 size_t DEVLINK_ATTR_SB_POOL_TYPE ; 
 scalar_t__ DEVLINK_SB_POOL_TYPE_EGRESS ; 
 scalar_t__ DEVLINK_SB_POOL_TYPE_INGRESS ; 
 int EINVAL ; 
 scalar_t__ nla_get_u8 (struct nlattr*) ; 

__attribute__((used)) static int
devlink_sb_pool_type_get_from_attrs(struct nlattr **attrs,
				    enum devlink_sb_pool_type *p_pool_type)
{
	u8 val;

	if (!attrs[DEVLINK_ATTR_SB_POOL_TYPE])
		return -EINVAL;

	val = nla_get_u8(attrs[DEVLINK_ATTR_SB_POOL_TYPE]);
	if (val != DEVLINK_SB_POOL_TYPE_INGRESS &&
	    val != DEVLINK_SB_POOL_TYPE_EGRESS)
		return -EINVAL;
	*p_pool_type = val;
	return 0;
}