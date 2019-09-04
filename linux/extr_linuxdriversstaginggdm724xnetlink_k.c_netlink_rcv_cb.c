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
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct nlmsghdr {scalar_t__ nlmsg_len; int /*<<< orphan*/  nlmsg_type; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ND_IFINDEX_LEN ; 
 scalar_t__ ND_MAX_MSG_LEN ; 
 void* ND_NLMSG_DATA (struct nlmsghdr*) ; 
 int /*<<< orphan*/  ND_NLMSG_IFIDX (struct nlmsghdr*) ; 
 int /*<<< orphan*/  ND_NLMSG_R_LEN (struct nlmsghdr*) ; 
 scalar_t__ NLMSG_HDRLEN ; 
 struct net_device* dev_get_by_index (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  rcv_cb (struct net_device*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void netlink_rcv_cb(struct sk_buff *skb)
{
	struct nlmsghdr	*nlh;
	struct net_device *dev;
	u32 mlen;
	void *msg;
	int ifindex;

	if (!rcv_cb) {
		pr_err("nl cb - unregistered\n");
		return;
	}

	if (skb->len < NLMSG_HDRLEN) {
		pr_err("nl cb - invalid skb length\n");
		return;
	}

	nlh = (struct nlmsghdr *)skb->data;

	if (skb->len < nlh->nlmsg_len || nlh->nlmsg_len > ND_MAX_MSG_LEN) {
		pr_err("nl cb - invalid length (%d,%d)\n",
		       skb->len, nlh->nlmsg_len);
		return;
	}

	memcpy(&ifindex, ND_NLMSG_IFIDX(nlh), ND_IFINDEX_LEN);
	msg = ND_NLMSG_DATA(nlh);
	mlen = ND_NLMSG_R_LEN(nlh);

	dev = dev_get_by_index(&init_net, ifindex);
	if (dev) {
		rcv_cb(dev, nlh->nlmsg_type, msg, mlen);
		dev_put(dev);
	} else {
		pr_err("nl cb - dev (%d) not found\n", ifindex);
	}
}