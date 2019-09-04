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
typedef  int u32 ;
struct udphdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; int /*<<< orphan*/  check; int /*<<< orphan*/  len; } ;
struct udp_table {int dummy; } ;
struct sock {struct dst_entry* sk_rx_dst; } ;
struct sk_buff {int len; int /*<<< orphan*/  dev; } ;
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;
struct dst_entry {int dummy; } ;
struct TYPE_4__ {struct in6_addr daddr; struct in6_addr saddr; } ;
struct TYPE_3__ {int /*<<< orphan*/  no_check6_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMPV6_DEST_UNREACH ; 
 int /*<<< orphan*/  ICMPV6_PORT_UNREACH ; 
 int IPPROTO_UDP ; 
 int IPPROTO_UDPLITE ; 
 int /*<<< orphan*/  UDP_MIB_CSUMERRORS ; 
 int /*<<< orphan*/  UDP_MIB_INERRORS ; 
 int /*<<< orphan*/  UDP_MIB_NOPORTS ; 
 int /*<<< orphan*/  XFRM_POLICY_IN ; 
 int /*<<< orphan*/  __UDP6_INC_STATS (struct net*,int /*<<< orphan*/ ,int) ; 
 struct sock* __udp6_lib_lookup_skb (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct udp_table*) ; 
 int __udp6_lib_mcast_deliver (struct net*,struct sk_buff*,struct in6_addr const*,struct in6_addr const*,struct udp_table*,int) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icmpv6_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ipv6_addr_is_multicast (struct in6_addr const*) ; 
 TYPE_2__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  net_dbg_ratelimited (char*,char*,struct in6_addr const*,int,int,int,struct in6_addr const*,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 scalar_t__ pskb_trim_rcsum (struct sk_buff*,int) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 struct sock* skb_steal_sock (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 scalar_t__ udp6_csum_init (struct sk_buff*,struct udphdr*,int) ; 
 int /*<<< orphan*/  udp6_csum_zero_error (struct sk_buff*) ; 
 int /*<<< orphan*/  udp6_sk_rx_dst_set (struct sock*,struct dst_entry*) ; 
 int udp6_unicast_rcv_skb (struct sock*,struct sk_buff*,struct udphdr*) ; 
 struct udphdr* udp_hdr (struct sk_buff*) ; 
 scalar_t__ udp_lib_checksum_complete (struct sk_buff*) ; 
 TYPE_1__* udp_sk (struct sock*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xfrm6_policy_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*) ; 

int __udp6_lib_rcv(struct sk_buff *skb, struct udp_table *udptable,
		   int proto)
{
	const struct in6_addr *saddr, *daddr;
	struct net *net = dev_net(skb->dev);
	struct udphdr *uh;
	struct sock *sk;
	u32 ulen = 0;

	if (!pskb_may_pull(skb, sizeof(struct udphdr)))
		goto discard;

	saddr = &ipv6_hdr(skb)->saddr;
	daddr = &ipv6_hdr(skb)->daddr;
	uh = udp_hdr(skb);

	ulen = ntohs(uh->len);
	if (ulen > skb->len)
		goto short_packet;

	if (proto == IPPROTO_UDP) {
		/* UDP validates ulen. */

		/* Check for jumbo payload */
		if (ulen == 0)
			ulen = skb->len;

		if (ulen < sizeof(*uh))
			goto short_packet;

		if (ulen < skb->len) {
			if (pskb_trim_rcsum(skb, ulen))
				goto short_packet;
			saddr = &ipv6_hdr(skb)->saddr;
			daddr = &ipv6_hdr(skb)->daddr;
			uh = udp_hdr(skb);
		}
	}

	if (udp6_csum_init(skb, uh, proto))
		goto csum_error;

	/* Check if the socket is already available, e.g. due to early demux */
	sk = skb_steal_sock(skb);
	if (sk) {
		struct dst_entry *dst = skb_dst(skb);
		int ret;

		if (unlikely(sk->sk_rx_dst != dst))
			udp6_sk_rx_dst_set(sk, dst);

		if (!uh->check && !udp_sk(sk)->no_check6_rx) {
			sock_put(sk);
			goto report_csum_error;
		}

		ret = udp6_unicast_rcv_skb(sk, skb, uh);
		sock_put(sk);
		return ret;
	}

	/*
	 *	Multicast receive code
	 */
	if (ipv6_addr_is_multicast(daddr))
		return __udp6_lib_mcast_deliver(net, skb,
				saddr, daddr, udptable, proto);

	/* Unicast */
	sk = __udp6_lib_lookup_skb(skb, uh->source, uh->dest, udptable);
	if (sk) {
		if (!uh->check && !udp_sk(sk)->no_check6_rx)
			goto report_csum_error;
		return udp6_unicast_rcv_skb(sk, skb, uh);
	}

	if (!uh->check)
		goto report_csum_error;

	if (!xfrm6_policy_check(NULL, XFRM_POLICY_IN, skb))
		goto discard;

	if (udp_lib_checksum_complete(skb))
		goto csum_error;

	__UDP6_INC_STATS(net, UDP_MIB_NOPORTS, proto == IPPROTO_UDPLITE);
	icmpv6_send(skb, ICMPV6_DEST_UNREACH, ICMPV6_PORT_UNREACH, 0);

	kfree_skb(skb);
	return 0;

short_packet:
	net_dbg_ratelimited("UDP%sv6: short packet: From [%pI6c]:%u %d/%d to [%pI6c]:%u\n",
			    proto == IPPROTO_UDPLITE ? "-Lite" : "",
			    saddr, ntohs(uh->source),
			    ulen, skb->len,
			    daddr, ntohs(uh->dest));
	goto discard;

report_csum_error:
	udp6_csum_zero_error(skb);
csum_error:
	__UDP6_INC_STATS(net, UDP_MIB_CSUMERRORS, proto == IPPROTO_UDPLITE);
discard:
	__UDP6_INC_STATS(net, UDP_MIB_INERRORS, proto == IPPROTO_UDPLITE);
	kfree_skb(skb);
	return 0;
}