#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct udphdr {scalar_t__ check; int /*<<< orphan*/  len; int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct sock {int dummy; } ;
struct sk_buff {int len; scalar_t__ ip_summed; struct sock* sk; } ;
struct inet_cork {int gso_size; scalar_t__ fragsize; } ;
struct flowi6 {int /*<<< orphan*/  flowi6_proto; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  fl6_dport; int /*<<< orphan*/  fl6_sport; } ;
typedef  int /*<<< orphan*/  __wsum ;
struct TYPE_6__ {int /*<<< orphan*/  recverr; } ;
struct TYPE_5__ {int gso_size; int /*<<< orphan*/  gso_segs; int /*<<< orphan*/  gso_type; } ;
struct TYPE_4__ {scalar_t__ no_check6_tx; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_NONE ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 scalar_t__ CSUM_MANGLED_0 ; 
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 
 int EIO ; 
 int ENOBUFS ; 
 int IS_UDPLITE (struct sock*) ; 
 int /*<<< orphan*/  SKB_GSO_UDP_L4 ; 
 int /*<<< orphan*/  UDP6_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int UDP_MAX_SEGMENTS ; 
 int /*<<< orphan*/  UDP_MIB_OUTDATAGRAMS ; 
 int /*<<< orphan*/  UDP_MIB_SNDBUFERRORS ; 
 scalar_t__ csum_ipv6_magic (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dst_xfrm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 TYPE_3__* inet6_sk (struct sock*) ; 
 int ip6_send_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst (struct sk_buff*) ; 
 int skb_network_header_len (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int skb_transport_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  udp6_hwcsum_outgoing (struct sock*,struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  udp_csum (struct sk_buff*) ; 
 struct udphdr* udp_hdr (struct sk_buff*) ; 
 TYPE_1__* udp_sk (struct sock*) ; 
 int /*<<< orphan*/  udplite_csum (struct sk_buff*) ; 

__attribute__((used)) static int udp_v6_send_skb(struct sk_buff *skb, struct flowi6 *fl6,
			   struct inet_cork *cork)
{
	struct sock *sk = skb->sk;
	struct udphdr *uh;
	int err = 0;
	int is_udplite = IS_UDPLITE(sk);
	__wsum csum = 0;
	int offset = skb_transport_offset(skb);
	int len = skb->len - offset;
	int datalen = len - sizeof(*uh);

	/*
	 * Create a UDP header
	 */
	uh = udp_hdr(skb);
	uh->source = fl6->fl6_sport;
	uh->dest = fl6->fl6_dport;
	uh->len = htons(len);
	uh->check = 0;

	if (cork->gso_size) {
		const int hlen = skb_network_header_len(skb) +
				 sizeof(struct udphdr);

		if (hlen + cork->gso_size > cork->fragsize) {
			kfree_skb(skb);
			return -EINVAL;
		}
		if (skb->len > cork->gso_size * UDP_MAX_SEGMENTS) {
			kfree_skb(skb);
			return -EINVAL;
		}
		if (udp_sk(sk)->no_check6_tx) {
			kfree_skb(skb);
			return -EINVAL;
		}
		if (skb->ip_summed != CHECKSUM_PARTIAL || is_udplite ||
		    dst_xfrm(skb_dst(skb))) {
			kfree_skb(skb);
			return -EIO;
		}

		if (datalen > cork->gso_size) {
			skb_shinfo(skb)->gso_size = cork->gso_size;
			skb_shinfo(skb)->gso_type = SKB_GSO_UDP_L4;
			skb_shinfo(skb)->gso_segs = DIV_ROUND_UP(datalen,
								 cork->gso_size);
		}
		goto csum_partial;
	}

	if (is_udplite)
		csum = udplite_csum(skb);
	else if (udp_sk(sk)->no_check6_tx) {   /* UDP csum disabled */
		skb->ip_summed = CHECKSUM_NONE;
		goto send;
	} else if (skb->ip_summed == CHECKSUM_PARTIAL) { /* UDP hardware csum */
csum_partial:
		udp6_hwcsum_outgoing(sk, skb, &fl6->saddr, &fl6->daddr, len);
		goto send;
	} else
		csum = udp_csum(skb);

	/* add protocol-dependent pseudo-header */
	uh->check = csum_ipv6_magic(&fl6->saddr, &fl6->daddr,
				    len, fl6->flowi6_proto, csum);
	if (uh->check == 0)
		uh->check = CSUM_MANGLED_0;

send:
	err = ip6_send_skb(skb);
	if (err) {
		if (err == -ENOBUFS && !inet6_sk(sk)->recverr) {
			UDP6_INC_STATS(sock_net(sk),
				       UDP_MIB_SNDBUFERRORS, is_udplite);
			err = 0;
		}
	} else {
		UDP6_INC_STATS(sock_net(sk),
			       UDP_MIB_OUTDATAGRAMS, is_udplite);
	}
	return err;
}