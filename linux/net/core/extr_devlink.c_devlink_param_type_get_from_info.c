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
struct genl_info {int /*<<< orphan*/ * attrs; } ;
typedef  enum devlink_param_type { ____Placeholder_devlink_param_type } devlink_param_type ;

/* Variables and functions */
 size_t DEVLINK_ATTR_PARAM_TYPE ; 
 int DEVLINK_PARAM_TYPE_BOOL ; 
 int DEVLINK_PARAM_TYPE_STRING ; 
 int DEVLINK_PARAM_TYPE_U16 ; 
 int DEVLINK_PARAM_TYPE_U32 ; 
 int DEVLINK_PARAM_TYPE_U8 ; 
 int EINVAL ; 
#define  NLA_FLAG 132 
#define  NLA_STRING 131 
#define  NLA_U16 130 
#define  NLA_U32 129 
#define  NLA_U8 128 
 int nla_get_u8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
devlink_param_type_get_from_info(struct genl_info *info,
				 enum devlink_param_type *param_type)
{
	if (!info->attrs[DEVLINK_ATTR_PARAM_TYPE])
		return -EINVAL;

	switch (nla_get_u8(info->attrs[DEVLINK_ATTR_PARAM_TYPE])) {
	case NLA_U8:
		*param_type = DEVLINK_PARAM_TYPE_U8;
		break;
	case NLA_U16:
		*param_type = DEVLINK_PARAM_TYPE_U16;
		break;
	case NLA_U32:
		*param_type = DEVLINK_PARAM_TYPE_U32;
		break;
	case NLA_STRING:
		*param_type = DEVLINK_PARAM_TYPE_STRING;
		break;
	case NLA_FLAG:
		*param_type = DEVLINK_PARAM_TYPE_BOOL;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}