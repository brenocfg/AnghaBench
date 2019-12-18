#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct hsr_priv {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_portid; int /*<<< orphan*/  snd_seq; struct nlattr** attrs; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t HSR_A_IFINDEX ; 
 int /*<<< orphan*/  HSR_A_NODE_ADDR ; 
 int /*<<< orphan*/  HSR_C_SET_NODE_LIST ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 struct net_device* __dev_get_by_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genl_info_net (struct genl_info*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 struct sk_buff* genlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsr_genl_family ; 
 void* hsr_get_next_node (struct hsr_priv*,void*,unsigned char*) ; 
 int /*<<< orphan*/  is_hsr_master (struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct hsr_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netlink_ack (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,unsigned char*) ; 
 int nla_put_u32 (struct sk_buff*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int hsr_get_node_list(struct sk_buff *skb_in, struct genl_info *info)
{
	/* For receiving */
	struct nlattr *na;
	struct net_device *hsr_dev;

	/* For sending */
	struct sk_buff *skb_out;
	void *msg_head;
	struct hsr_priv *hsr;
	void *pos;
	unsigned char addr[ETH_ALEN];
	int res;

	if (!info)
		goto invalid;

	na = info->attrs[HSR_A_IFINDEX];
	if (!na)
		goto invalid;

	hsr_dev = __dev_get_by_index(genl_info_net(info),
				     nla_get_u32(info->attrs[HSR_A_IFINDEX]));
	if (!hsr_dev)
		goto invalid;
	if (!is_hsr_master(hsr_dev))
		goto invalid;

	/* Send reply */
	skb_out = genlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	if (!skb_out) {
		res = -ENOMEM;
		goto fail;
	}

	msg_head = genlmsg_put(skb_out, NETLINK_CB(skb_in).portid,
			       info->snd_seq, &hsr_genl_family, 0,
			       HSR_C_SET_NODE_LIST);
	if (!msg_head) {
		res = -ENOMEM;
		goto nla_put_failure;
	}

	res = nla_put_u32(skb_out, HSR_A_IFINDEX, hsr_dev->ifindex);
	if (res < 0)
		goto nla_put_failure;

	hsr = netdev_priv(hsr_dev);

	rcu_read_lock();
	pos = hsr_get_next_node(hsr, NULL, addr);
	while (pos) {
		res = nla_put(skb_out, HSR_A_NODE_ADDR, ETH_ALEN, addr);
		if (res < 0) {
			rcu_read_unlock();
			goto nla_put_failure;
		}
		pos = hsr_get_next_node(hsr, pos, addr);
	}
	rcu_read_unlock();

	genlmsg_end(skb_out, msg_head);
	genlmsg_unicast(genl_info_net(info), skb_out, info->snd_portid);

	return 0;

invalid:
	netlink_ack(skb_in, nlmsg_hdr(skb_in), -EINVAL, NULL);
	return 0;

nla_put_failure:
	kfree_skb(skb_out);
	/* Fall through */

fail:
	return res;
}