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
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlmsgerr {int error; int /*<<< orphan*/  msg; } ;
struct net_device {int dummy; } ;
struct net {int /*<<< orphan*/  genl_sock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  NLMSG_ERROR ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct nlmsghdr*,int) ; 
 scalar_t__ nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int nlmsg_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 

int ncsi_send_netlink_err(struct net_device *dev,
			  u32 snd_seq,
			  u32 snd_portid,
			  struct nlmsghdr *nlhdr,
			  int err)
{
	struct nlmsghdr *nlh;
	struct nlmsgerr *nle;
	struct sk_buff *skb;
	struct net *net;

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	if (!skb)
		return -ENOMEM;

	net = dev_net(dev);

	nlh = nlmsg_put(skb, snd_portid, snd_seq,
			NLMSG_ERROR, sizeof(*nle), 0);
	nle = (struct nlmsgerr *)nlmsg_data(nlh);
	nle->error = err;
	memcpy(&nle->msg, nlhdr, sizeof(*nlh));

	nlmsg_end(skb, nlh);

	return nlmsg_unicast(net->genl_sock, skb, snd_portid);
}