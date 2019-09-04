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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 size_t BATADV_ATTR_MESH_IFINDEX ; 
 int /*<<< orphan*/  BATADV_CMD_GET_MESH_INFO ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  batadv_netlink_family ; 
 int batadv_netlink_mesh_info_put (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  batadv_softif_is_valid (struct net_device*) ; 
 struct net_device* dev_get_by_index (struct net*,int) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct net* genl_info_net (struct genl_info*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int nla_get_u32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
batadv_netlink_get_mesh_info(struct sk_buff *skb, struct genl_info *info)
{
	struct net *net = genl_info_net(info);
	struct net_device *soft_iface;
	struct sk_buff *msg = NULL;
	void *msg_head;
	int ifindex;
	int ret;

	if (!info->attrs[BATADV_ATTR_MESH_IFINDEX])
		return -EINVAL;

	ifindex = nla_get_u32(info->attrs[BATADV_ATTR_MESH_IFINDEX]);
	if (!ifindex)
		return -EINVAL;

	soft_iface = dev_get_by_index(net, ifindex);
	if (!soft_iface || !batadv_softif_is_valid(soft_iface)) {
		ret = -ENODEV;
		goto out;
	}

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg) {
		ret = -ENOMEM;
		goto out;
	}

	msg_head = genlmsg_put(msg, info->snd_portid, info->snd_seq,
			       &batadv_netlink_family, 0,
			       BATADV_CMD_GET_MESH_INFO);
	if (!msg_head) {
		ret = -ENOBUFS;
		goto out;
	}

	ret = batadv_netlink_mesh_info_put(msg, soft_iface);

 out:
	if (soft_iface)
		dev_put(soft_iface);

	if (ret) {
		if (msg)
			nlmsg_free(msg);
		return ret;
	}

	genlmsg_end(msg, msg_head);
	return genlmsg_reply(msg, info);
}