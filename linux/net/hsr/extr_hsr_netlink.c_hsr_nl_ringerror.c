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
struct hsr_priv {int dummy; } ;
struct hsr_port {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HSR_A_IFINDEX ; 
 int /*<<< orphan*/  HSR_A_NODE_ADDR ; 
 int /*<<< orphan*/  HSR_C_RING_ERROR ; 
 int /*<<< orphan*/  HSR_PT_MASTER ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_multicast (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* genlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsr_genl_family ; 
 struct hsr_port* hsr_port_get_hsr (struct hsr_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_warn (TYPE_1__*,char*) ; 
 int nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void hsr_nl_ringerror(struct hsr_priv *hsr, unsigned char addr[ETH_ALEN],
		      struct hsr_port *port)
{
	struct sk_buff *skb;
	void *msg_head;
	struct hsr_port *master;
	int res;

	skb = genlmsg_new(NLMSG_GOODSIZE, GFP_ATOMIC);
	if (!skb)
		goto fail;

	msg_head = genlmsg_put(skb, 0, 0, &hsr_genl_family, 0,
			       HSR_C_RING_ERROR);
	if (!msg_head)
		goto nla_put_failure;

	res = nla_put(skb, HSR_A_NODE_ADDR, ETH_ALEN, addr);
	if (res < 0)
		goto nla_put_failure;

	res = nla_put_u32(skb, HSR_A_IFINDEX, port->dev->ifindex);
	if (res < 0)
		goto nla_put_failure;

	genlmsg_end(skb, msg_head);
	genlmsg_multicast(&hsr_genl_family, skb, 0, 0, GFP_ATOMIC);

	return;

nla_put_failure:
	kfree_skb(skb);

fail:
	rcu_read_lock();
	master = hsr_port_get_hsr(hsr, HSR_PT_MASTER);
	netdev_warn(master->dev, "Could not send HSR ring error message\n");
	rcu_read_unlock();
}