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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct sockaddr_pn {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_bound_dev_if; } ;
struct sk_buff {void* pkt_type; } ;
struct pn_sock {scalar_t__ sobject; scalar_t__ dobject; scalar_t__ resource; } ;
struct net_device {int flags; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int IFF_UP ; 
 void* PACKET_LOOPBACK ; 
 scalar_t__ PN_NO_ADDR ; 
 struct net_device* dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ phonet_address_get (struct net_device*,scalar_t__) ; 
 scalar_t__ phonet_address_lookup (struct net*,scalar_t__) ; 
 struct net_device* phonet_device_get (struct net*) ; 
 struct net_device* phonet_route_output (struct net*,scalar_t__) ; 
 scalar_t__ pn_addr (scalar_t__) ; 
 struct sock* pn_find_sock_by_res (struct net*,scalar_t__) ; 
 int /*<<< orphan*/  pn_obj (scalar_t__) ; 
 scalar_t__ pn_object (scalar_t__,int /*<<< orphan*/ ) ; 
 int pn_send (struct sk_buff*,struct net_device*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct pn_sock* pn_sk (struct sock*) ; 
 scalar_t__ pn_sockaddr_get_object (struct sockaddr_pn const*) ; 
 scalar_t__ pn_sockaddr_get_resource (struct sockaddr_pn const*) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

int pn_skb_send(struct sock *sk, struct sk_buff *skb,
		const struct sockaddr_pn *target)
{
	struct net *net = sock_net(sk);
	struct net_device *dev;
	struct pn_sock *pn = pn_sk(sk);
	int err;
	u16 src, dst;
	u8 daddr, saddr, res;

	src = pn->sobject;
	if (target != NULL) {
		dst = pn_sockaddr_get_object(target);
		res = pn_sockaddr_get_resource(target);
	} else {
		dst = pn->dobject;
		res = pn->resource;
	}
	daddr = pn_addr(dst);

	err = -EHOSTUNREACH;
	if (sk->sk_bound_dev_if)
		dev = dev_get_by_index(net, sk->sk_bound_dev_if);
	else if (phonet_address_lookup(net, daddr) == 0) {
		dev = phonet_device_get(net);
		skb->pkt_type = PACKET_LOOPBACK;
	} else if (dst == 0) {
		/* Resource routing (small race until phonet_rcv()) */
		struct sock *sk = pn_find_sock_by_res(net, res);
		if (sk)	{
			sock_put(sk);
			dev = phonet_device_get(net);
			skb->pkt_type = PACKET_LOOPBACK;
		} else
			dev = phonet_route_output(net, daddr);
	} else
		dev = phonet_route_output(net, daddr);

	if (!dev || !(dev->flags & IFF_UP))
		goto drop;

	saddr = phonet_address_get(dev, daddr);
	if (saddr == PN_NO_ADDR)
		goto drop;

	if (!pn_addr(src))
		src = pn_object(saddr, pn_obj(src));

	err = pn_send(skb, dev, dst, src, res, 0);
	dev_put(dev);
	return err;

drop:
	kfree_skb(skb);
	if (dev)
		dev_put(dev);
	return err;
}