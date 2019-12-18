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
struct sk_buff {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; scalar_t__* attrs; } ;
struct genl_family {int /*<<< orphan*/  netnsok; } ;

/* Variables and functions */
 size_t CTRL_ATTR_FAMILY_ID ; 
 size_t CTRL_ATTR_FAMILY_NAME ; 
 int /*<<< orphan*/  CTRL_CMD_NEWFAMILY ; 
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  NETLINK_GENERIC ; 
 int /*<<< orphan*/  PF_NETLINK ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  cb_lock ; 
 struct sk_buff* ctrl_build_family_msg (struct genl_family const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct genl_family* genl_family_find_byid (int /*<<< orphan*/ ) ; 
 struct genl_family* genl_family_find_byname (char*) ; 
 int /*<<< orphan*/  genl_info_net (struct genl_info*) ; 
 int /*<<< orphan*/  genl_lock () ; 
 int /*<<< orphan*/  genl_unlock () ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* nla_data (scalar_t__) ; 
 int /*<<< orphan*/  nla_get_u16 (scalar_t__) ; 
 int /*<<< orphan*/  request_module (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ctrl_getfamily(struct sk_buff *skb, struct genl_info *info)
{
	struct sk_buff *msg;
	const struct genl_family *res = NULL;
	int err = -EINVAL;

	if (info->attrs[CTRL_ATTR_FAMILY_ID]) {
		u16 id = nla_get_u16(info->attrs[CTRL_ATTR_FAMILY_ID]);
		res = genl_family_find_byid(id);
		err = -ENOENT;
	}

	if (info->attrs[CTRL_ATTR_FAMILY_NAME]) {
		char *name;

		name = nla_data(info->attrs[CTRL_ATTR_FAMILY_NAME]);
		res = genl_family_find_byname(name);
#ifdef CONFIG_MODULES
		if (res == NULL) {
			genl_unlock();
			up_read(&cb_lock);
			request_module("net-pf-%d-proto-%d-family-%s",
				       PF_NETLINK, NETLINK_GENERIC, name);
			down_read(&cb_lock);
			genl_lock();
			res = genl_family_find_byname(name);
		}
#endif
		err = -ENOENT;
	}

	if (res == NULL)
		return err;

	if (!res->netnsok && !net_eq(genl_info_net(info), &init_net)) {
		/* family doesn't exist here */
		return -ENOENT;
	}

	msg = ctrl_build_family_msg(res, info->snd_portid, info->snd_seq,
				    CTRL_CMD_NEWFAMILY);
	if (IS_ERR(msg))
		return PTR_ERR(msg);

	return genlmsg_reply(msg, info);
}