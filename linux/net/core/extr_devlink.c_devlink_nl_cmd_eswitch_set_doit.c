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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct genl_info {int /*<<< orphan*/  extack; scalar_t__* attrs; struct devlink** user_ptr; } ;
struct devlink_ops {int (* eswitch_mode_set ) (struct devlink*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* eswitch_inline_mode_set ) (struct devlink*,void*,int /*<<< orphan*/ ) ;int (* eswitch_encap_mode_set ) (struct devlink*,int,int /*<<< orphan*/ ) ;} ;
struct devlink {struct devlink_ops* ops; } ;
typedef  enum devlink_eswitch_encap_mode { ____Placeholder_devlink_eswitch_encap_mode } devlink_eswitch_encap_mode ;

/* Variables and functions */
 size_t DEVLINK_ATTR_ESWITCH_ENCAP_MODE ; 
 size_t DEVLINK_ATTR_ESWITCH_INLINE_MODE ; 
 size_t DEVLINK_ATTR_ESWITCH_MODE ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  nla_get_u16 (scalar_t__) ; 
 void* nla_get_u8 (scalar_t__) ; 
 int stub1 (struct devlink*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (struct devlink*,void*,int /*<<< orphan*/ ) ; 
 int stub3 (struct devlink*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_nl_cmd_eswitch_set_doit(struct sk_buff *skb,
					   struct genl_info *info)
{
	struct devlink *devlink = info->user_ptr[0];
	const struct devlink_ops *ops = devlink->ops;
	enum devlink_eswitch_encap_mode encap_mode;
	u8 inline_mode;
	int err = 0;
	u16 mode;

	if (info->attrs[DEVLINK_ATTR_ESWITCH_MODE]) {
		if (!ops->eswitch_mode_set)
			return -EOPNOTSUPP;
		mode = nla_get_u16(info->attrs[DEVLINK_ATTR_ESWITCH_MODE]);
		err = ops->eswitch_mode_set(devlink, mode, info->extack);
		if (err)
			return err;
	}

	if (info->attrs[DEVLINK_ATTR_ESWITCH_INLINE_MODE]) {
		if (!ops->eswitch_inline_mode_set)
			return -EOPNOTSUPP;
		inline_mode = nla_get_u8(
				info->attrs[DEVLINK_ATTR_ESWITCH_INLINE_MODE]);
		err = ops->eswitch_inline_mode_set(devlink, inline_mode,
						   info->extack);
		if (err)
			return err;
	}

	if (info->attrs[DEVLINK_ATTR_ESWITCH_ENCAP_MODE]) {
		if (!ops->eswitch_encap_mode_set)
			return -EOPNOTSUPP;
		encap_mode = nla_get_u8(info->attrs[DEVLINK_ATTR_ESWITCH_ENCAP_MODE]);
		err = ops->eswitch_encap_mode_set(devlink, encap_mode,
						  info->extack);
		if (err)
			return err;
	}

	return 0;
}