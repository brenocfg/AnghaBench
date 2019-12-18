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
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct ncsi_request {int /*<<< orphan*/  snd_portid; TYPE_1__* rsp; int /*<<< orphan*/  snd_seq; } ;
struct ncsi_package {int /*<<< orphan*/  id; } ;
struct ncsi_channel {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  ifindex; } ;
struct TYPE_3__ {scalar_t__ data; int /*<<< orphan*/  len; TYPE_2__* dev; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NCSI_ATTR_CHANNEL_ID ; 
 int /*<<< orphan*/  NCSI_ATTR_DATA ; 
 int /*<<< orphan*/  NCSI_ATTR_IFINDEX ; 
 int /*<<< orphan*/  NCSI_ATTR_PACKAGE_ID ; 
 int /*<<< orphan*/  NCSI_CMD_SEND_CMD ; 
 int /*<<< orphan*/  NCSI_RESERVED_CHANNEL ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 struct net* dev_net (TYPE_2__*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 struct sk_buff* genlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int genlmsg_unicast (struct net*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ncsi_genl_family ; 
 int nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ncsi_send_netlink_rsp(struct ncsi_request *nr,
			  struct ncsi_package *np,
			  struct ncsi_channel *nc)
{
	struct sk_buff *skb;
	struct net *net;
	void *hdr;
	int rc;

	net = dev_net(nr->rsp->dev);

	skb = genlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	if (!skb)
		return -ENOMEM;

	hdr = genlmsg_put(skb, nr->snd_portid, nr->snd_seq,
			  &ncsi_genl_family, 0, NCSI_CMD_SEND_CMD);
	if (!hdr) {
		kfree_skb(skb);
		return -EMSGSIZE;
	}

	nla_put_u32(skb, NCSI_ATTR_IFINDEX, nr->rsp->dev->ifindex);
	if (np)
		nla_put_u32(skb, NCSI_ATTR_PACKAGE_ID, np->id);
	if (nc)
		nla_put_u32(skb, NCSI_ATTR_CHANNEL_ID, nc->id);
	else
		nla_put_u32(skb, NCSI_ATTR_CHANNEL_ID, NCSI_RESERVED_CHANNEL);

	rc = nla_put(skb, NCSI_ATTR_DATA, nr->rsp->len, (void *)nr->rsp->data);
	if (rc)
		goto err;

	genlmsg_end(skb, hdr);
	return genlmsg_unicast(net, skb, nr->snd_portid);

err:
	kfree_skb(skb);
	return rc;
}