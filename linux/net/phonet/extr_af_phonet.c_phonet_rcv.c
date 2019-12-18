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
typedef  int u16 ;
struct sockaddr_pn {int /*<<< orphan*/  spn_resource; } ;
struct sock {int dummy; } ;
struct sk_buff {int len; scalar_t__ pkt_type; struct net_device* dev; } ;
struct phonethdr {int /*<<< orphan*/  pn_length; } ;
struct packet_type {int dummy; } ;
struct net_device {int /*<<< orphan*/  hard_header_len; int /*<<< orphan*/  name; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_PHONET ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NET_RX_DROP ; 
 int NET_RX_SUCCESS ; 
 scalar_t__ PACKET_LOOPBACK ; 
 scalar_t__ PNADDR_BROADCAST ; 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,int) ; 
 scalar_t__ can_respond (struct sk_buff*) ; 
 scalar_t__ dev_hard_header (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 int get_unaligned_be16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  net_dbg_ratelimited (char*,scalar_t__,...) ; 
 scalar_t__ phonet_address_lookup (struct net*,scalar_t__) ; 
 struct net_device* phonet_route_output (struct net*,scalar_t__) ; 
 int /*<<< orphan*/  pn_deliver_sock_broadcast (struct net*,struct sk_buff*) ; 
 struct sock* pn_find_sock_by_res (struct net*,int /*<<< orphan*/ ) ; 
 struct sock* pn_find_sock_by_sa (struct net*,struct sockaddr_pn*) ; 
 struct phonethdr* pn_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  pn_skb_get_dst_sockaddr (struct sk_buff*,struct sockaddr_pn*) ; 
 scalar_t__ pn_sockaddr_get_addr (struct sockaddr_pn*) ; 
 scalar_t__ pn_sockaddr_get_object (struct sockaddr_pn*) ; 
 int /*<<< orphan*/  pskb_pull (struct sk_buff*,int) ; 
 scalar_t__ pskb_trim (struct sk_buff*,int) ; 
 int /*<<< orphan*/  send_obj_unreachable (struct sk_buff*) ; 
 int /*<<< orphan*/  send_reset_indications (struct sk_buff*) ; 
 int sk_receive_skb (struct sock*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 struct sk_buff* skb_share_check (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int phonet_rcv(struct sk_buff *skb, struct net_device *dev,
			struct packet_type *pkttype,
			struct net_device *orig_dev)
{
	struct net *net = dev_net(dev);
	struct phonethdr *ph;
	struct sockaddr_pn sa;
	u16 len;

	skb = skb_share_check(skb, GFP_ATOMIC);
	if (!skb)
		return NET_RX_DROP;

	/* check we have at least a full Phonet header */
	if (!pskb_pull(skb, sizeof(struct phonethdr)))
		goto out;

	/* check that the advertised length is correct */
	ph = pn_hdr(skb);
	len = get_unaligned_be16(&ph->pn_length);
	if (len < 2)
		goto out;
	len -= 2;
	if ((len > skb->len) || pskb_trim(skb, len))
		goto out;
	skb_reset_transport_header(skb);

	pn_skb_get_dst_sockaddr(skb, &sa);

	/* check if this is broadcasted */
	if (pn_sockaddr_get_addr(&sa) == PNADDR_BROADCAST) {
		pn_deliver_sock_broadcast(net, skb);
		goto out;
	}

	/* resource routing */
	if (pn_sockaddr_get_object(&sa) == 0) {
		struct sock *sk = pn_find_sock_by_res(net, sa.spn_resource);
		if (sk)
			return sk_receive_skb(sk, skb, 0);
	}

	/* check if we are the destination */
	if (phonet_address_lookup(net, pn_sockaddr_get_addr(&sa)) == 0) {
		/* Phonet packet input */
		struct sock *sk = pn_find_sock_by_sa(net, &sa);

		if (sk)
			return sk_receive_skb(sk, skb, 0);

		if (can_respond(skb)) {
			send_obj_unreachable(skb);
			send_reset_indications(skb);
		}
	} else if (unlikely(skb->pkt_type == PACKET_LOOPBACK))
		goto out; /* Race between address deletion and loopback */
	else {
		/* Phonet packet routing */
		struct net_device *out_dev;

		out_dev = phonet_route_output(net, pn_sockaddr_get_addr(&sa));
		if (!out_dev) {
			net_dbg_ratelimited("No Phonet route to %02X\n",
					    pn_sockaddr_get_addr(&sa));
			goto out;
		}

		__skb_push(skb, sizeof(struct phonethdr));
		skb->dev = out_dev;
		if (out_dev == dev) {
			net_dbg_ratelimited("Phonet loop to %02X on %s\n",
					    pn_sockaddr_get_addr(&sa),
					    dev->name);
			goto out_dev;
		}
		/* Some drivers (e.g. TUN) do not allocate HW header space */
		if (skb_cow_head(skb, out_dev->hard_header_len))
			goto out_dev;

		if (dev_hard_header(skb, out_dev, ETH_P_PHONET, NULL, NULL,
					skb->len) < 0)
			goto out_dev;
		dev_queue_xmit(skb);
		dev_put(out_dev);
		return NET_RX_SUCCESS;
out_dev:
		dev_put(out_dev);
	}

out:
	kfree_skb(skb);
	return NET_RX_DROP;
}