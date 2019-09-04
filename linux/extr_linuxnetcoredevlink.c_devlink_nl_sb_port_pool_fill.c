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
struct sk_buff {int dummy; } ;
struct devlink_sb {int /*<<< orphan*/  index; } ;
struct devlink_port {int /*<<< orphan*/  index; } ;
struct devlink_ops {int (* sb_port_pool_get ) (struct devlink_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int (* sb_occ_port_pool_get ) (struct devlink_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct devlink {struct devlink_ops* ops; } ;
typedef  enum devlink_command { ____Placeholder_devlink_command } devlink_command ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_PORT_INDEX ; 
 int /*<<< orphan*/  DEVLINK_ATTR_SB_INDEX ; 
 int /*<<< orphan*/  DEVLINK_ATTR_SB_OCC_CUR ; 
 int /*<<< orphan*/  DEVLINK_ATTR_SB_OCC_MAX ; 
 int /*<<< orphan*/  DEVLINK_ATTR_SB_POOL_INDEX ; 
 int /*<<< orphan*/  DEVLINK_ATTR_SB_THRESHOLD ; 
 int EMSGSIZE ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  devlink_nl_family ; 
 scalar_t__ devlink_nl_put_handle (struct sk_buff*,struct devlink*) ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct devlink_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub2 (struct devlink_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int devlink_nl_sb_port_pool_fill(struct sk_buff *msg,
					struct devlink *devlink,
					struct devlink_port *devlink_port,
					struct devlink_sb *devlink_sb,
					u16 pool_index,
					enum devlink_command cmd,
					u32 portid, u32 seq, int flags)
{
	const struct devlink_ops *ops = devlink->ops;
	u32 threshold;
	void *hdr;
	int err;

	err = ops->sb_port_pool_get(devlink_port, devlink_sb->index,
				    pool_index, &threshold);
	if (err)
		return err;

	hdr = genlmsg_put(msg, portid, seq, &devlink_nl_family, flags, cmd);
	if (!hdr)
		return -EMSGSIZE;

	if (devlink_nl_put_handle(msg, devlink))
		goto nla_put_failure;
	if (nla_put_u32(msg, DEVLINK_ATTR_PORT_INDEX, devlink_port->index))
		goto nla_put_failure;
	if (nla_put_u32(msg, DEVLINK_ATTR_SB_INDEX, devlink_sb->index))
		goto nla_put_failure;
	if (nla_put_u16(msg, DEVLINK_ATTR_SB_POOL_INDEX, pool_index))
		goto nla_put_failure;
	if (nla_put_u32(msg, DEVLINK_ATTR_SB_THRESHOLD, threshold))
		goto nla_put_failure;

	if (ops->sb_occ_port_pool_get) {
		u32 cur;
		u32 max;

		err = ops->sb_occ_port_pool_get(devlink_port, devlink_sb->index,
						pool_index, &cur, &max);
		if (err && err != -EOPNOTSUPP)
			return err;
		if (!err) {
			if (nla_put_u32(msg, DEVLINK_ATTR_SB_OCC_CUR, cur))
				goto nla_put_failure;
			if (nla_put_u32(msg, DEVLINK_ATTR_SB_OCC_MAX, max))
				goto nla_put_failure;
		}
	}

	genlmsg_end(msg, hdr);
	return 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}