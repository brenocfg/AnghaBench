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
struct sock {int /*<<< orphan*/  sk_bound_dev_if; } ;
struct sk_buff {int /*<<< orphan*/  protocol; struct net_device* dev; } ;
struct net_device {size_t name; int needed_tailroom; } ;
struct msghdr {int msg_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_IEEE802154 ; 
 int EMSGSIZE ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_P_IEEE802154 ; 
 unsigned int IEEE802154_MTU ; 
 int LL_RESERVED_SPACE (struct net_device*) ; 
 int MSG_DONTWAIT ; 
 int MSG_OOB ; 
 struct net_device* dev_get_by_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device* dev_getfirstbyhwtype (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int memcpy_from_msg (int /*<<< orphan*/ ,struct msghdr*,size_t) ; 
 int net_xmit_errno (int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 struct sk_buff* sock_alloc_send_skb (struct sock*,int,int,int*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

__attribute__((used)) static int raw_sendmsg(struct sock *sk, struct msghdr *msg, size_t size)
{
	struct net_device *dev;
	unsigned int mtu;
	struct sk_buff *skb;
	int hlen, tlen;
	int err;

	if (msg->msg_flags & MSG_OOB) {
		pr_debug("msg->msg_flags = 0x%x\n", msg->msg_flags);
		return -EOPNOTSUPP;
	}

	lock_sock(sk);
	if (!sk->sk_bound_dev_if)
		dev = dev_getfirstbyhwtype(sock_net(sk), ARPHRD_IEEE802154);
	else
		dev = dev_get_by_index(sock_net(sk), sk->sk_bound_dev_if);
	release_sock(sk);

	if (!dev) {
		pr_debug("no dev\n");
		err = -ENXIO;
		goto out;
	}

	mtu = IEEE802154_MTU;
	pr_debug("name = %s, mtu = %u\n", dev->name, mtu);

	if (size > mtu) {
		pr_debug("size = %zu, mtu = %u\n", size, mtu);
		err = -EMSGSIZE;
		goto out_dev;
	}

	hlen = LL_RESERVED_SPACE(dev);
	tlen = dev->needed_tailroom;
	skb = sock_alloc_send_skb(sk, hlen + tlen + size,
				  msg->msg_flags & MSG_DONTWAIT, &err);
	if (!skb)
		goto out_dev;

	skb_reserve(skb, hlen);

	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);

	err = memcpy_from_msg(skb_put(skb, size), msg, size);
	if (err < 0)
		goto out_skb;

	skb->dev = dev;
	skb->protocol = htons(ETH_P_IEEE802154);

	err = dev_queue_xmit(skb);
	if (err > 0)
		err = net_xmit_errno(err);

	dev_put(dev);

	return err ?: size;

out_skb:
	kfree_skb(skb);
out_dev:
	dev_put(dev);
out:
	return err;
}