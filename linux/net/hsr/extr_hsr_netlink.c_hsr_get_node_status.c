#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {int ifindex; } ;
struct hsr_priv {int dummy; } ;
struct hsr_port {TYPE_1__* dev; } ;
struct genl_info {int /*<<< orphan*/  snd_portid; struct nlattr** attrs; int /*<<< orphan*/  snd_seq; } ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;
struct TYPE_3__ {int ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t HSR_A_ADDR_B_IFINDEX ; 
 size_t HSR_A_IF1_AGE ; 
 size_t HSR_A_IF1_IFINDEX ; 
 int /*<<< orphan*/  HSR_A_IF1_SEQ ; 
 size_t HSR_A_IF2_AGE ; 
 size_t HSR_A_IF2_IFINDEX ; 
 int /*<<< orphan*/  HSR_A_IF2_SEQ ; 
 size_t HSR_A_IFINDEX ; 
 size_t HSR_A_NODE_ADDR ; 
 size_t HSR_A_NODE_ADDR_B ; 
 int /*<<< orphan*/  HSR_C_SET_NODE_STATUS ; 
 int /*<<< orphan*/  HSR_PT_SLAVE_A ; 
 int /*<<< orphan*/  HSR_PT_SLAVE_B ; 
 TYPE_2__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 struct net_device* __dev_get_by_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genl_info_net (struct genl_info*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 struct sk_buff* genlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsr_genl_family ; 
 int hsr_get_node_data (struct hsr_priv*,unsigned char*,unsigned char*,int*,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 struct hsr_port* hsr_port_get_hsr (struct hsr_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_hsr_master (struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct hsr_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netlink_ack (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned char* nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int nla_put (struct sk_buff*,size_t,int,unsigned char*) ; 
 int nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nla_put_u32 (struct sk_buff*,size_t,int) ; 
 int /*<<< orphan*/  nlmsg_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int hsr_get_node_status(struct sk_buff *skb_in, struct genl_info *info)
{
	/* For receiving */
	struct nlattr *na;
	struct net_device *hsr_dev;

	/* For sending */
	struct sk_buff *skb_out;
	void *msg_head;
	struct hsr_priv *hsr;
	struct hsr_port *port;
	unsigned char hsr_node_addr_b[ETH_ALEN];
	int hsr_node_if1_age;
	u16 hsr_node_if1_seq;
	int hsr_node_if2_age;
	u16 hsr_node_if2_seq;
	int addr_b_ifindex;
	int res;

	if (!info)
		goto invalid;

	na = info->attrs[HSR_A_IFINDEX];
	if (!na)
		goto invalid;
	na = info->attrs[HSR_A_NODE_ADDR];
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
			       HSR_C_SET_NODE_STATUS);
	if (!msg_head) {
		res = -ENOMEM;
		goto nla_put_failure;
	}

	res = nla_put_u32(skb_out, HSR_A_IFINDEX, hsr_dev->ifindex);
	if (res < 0)
		goto nla_put_failure;

	hsr = netdev_priv(hsr_dev);
	res = hsr_get_node_data(hsr,
				(unsigned char *)
				nla_data(info->attrs[HSR_A_NODE_ADDR]),
					 hsr_node_addr_b,
					 &addr_b_ifindex,
					 &hsr_node_if1_age,
					 &hsr_node_if1_seq,
					 &hsr_node_if2_age,
					 &hsr_node_if2_seq);
	if (res < 0)
		goto nla_put_failure;

	res = nla_put(skb_out, HSR_A_NODE_ADDR, ETH_ALEN,
		      nla_data(info->attrs[HSR_A_NODE_ADDR]));
	if (res < 0)
		goto nla_put_failure;

	if (addr_b_ifindex > -1) {
		res = nla_put(skb_out, HSR_A_NODE_ADDR_B, ETH_ALEN,
			      hsr_node_addr_b);
		if (res < 0)
			goto nla_put_failure;

		res = nla_put_u32(skb_out, HSR_A_ADDR_B_IFINDEX,
				  addr_b_ifindex);
		if (res < 0)
			goto nla_put_failure;
	}

	res = nla_put_u32(skb_out, HSR_A_IF1_AGE, hsr_node_if1_age);
	if (res < 0)
		goto nla_put_failure;
	res = nla_put_u16(skb_out, HSR_A_IF1_SEQ, hsr_node_if1_seq);
	if (res < 0)
		goto nla_put_failure;
	rcu_read_lock();
	port = hsr_port_get_hsr(hsr, HSR_PT_SLAVE_A);
	if (port)
		res = nla_put_u32(skb_out, HSR_A_IF1_IFINDEX,
				  port->dev->ifindex);
	rcu_read_unlock();
	if (res < 0)
		goto nla_put_failure;

	res = nla_put_u32(skb_out, HSR_A_IF2_AGE, hsr_node_if2_age);
	if (res < 0)
		goto nla_put_failure;
	res = nla_put_u16(skb_out, HSR_A_IF2_SEQ, hsr_node_if2_seq);
	if (res < 0)
		goto nla_put_failure;
	rcu_read_lock();
	port = hsr_port_get_hsr(hsr, HSR_PT_SLAVE_B);
	if (port)
		res = nla_put_u32(skb_out, HSR_A_IF2_IFINDEX,
				  port->dev->ifindex);
	rcu_read_unlock();
	if (res < 0)
		goto nla_put_failure;

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