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
struct udphdr {scalar_t__ check; int /*<<< orphan*/  len; int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct sock {int /*<<< orphan*/  sk_protocol; scalar_t__ sk_no_check_tx; } ;
struct sk_buff {int len; scalar_t__ ip_summed; struct sock* sk; } ;
struct inet_sock {int /*<<< orphan*/  recverr; int /*<<< orphan*/  inet_sport; } ;
struct inet_cork {int gso_size; scalar_t__ fragsize; } ;
struct flowi4 {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  fl4_dport; } ;
typedef  int /*<<< orphan*/  __wsum ;
struct TYPE_2__ {int gso_size; int /*<<< orphan*/  gso_segs; int /*<<< orphan*/  gso_type; } ;

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
 int /*<<< orphan*/  UDP_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int UDP_MAX_SEGMENTS ; 
 int /*<<< orphan*/  UDP_MIB_OUTDATAGRAMS ; 
 int /*<<< orphan*/  UDP_MIB_SNDBUFERRORS ; 
 scalar_t__ csum_tcpudp_magic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dst_xfrm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int ip_send_skb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst (struct sk_buff*) ; 
 int skb_network_header_len (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int skb_transport_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  udp4_hwcsum (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udp_csum (struct sk_buff*) ; 
 struct udphdr* udp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  udplite_csum (struct sk_buff*) ; 

__attribute__((used)) static int udp_send_skb(struct sk_buff *skb, struct flowi4 *fl4,
			struct inet_cork *cork)
{
	struct sock *sk = skb->sk;
	struct inet_sock *inet = inet_sk(sk);
	struct udphdr *uh;
	int err = 0;
	int is_udplite = IS_UDPLITE(sk);
	int offset = skb_transport_offset(skb);
	int len = skb->len - offset;
	int datalen = len - sizeof(*uh);
	__wsum csum = 0;

	/*
	 * Create a UDP header
	 */
	uh = udp_hdr(skb);
	uh->source = inet->inet_sport;
	uh->dest = fl4->fl4_dport;
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
		if (sk->sk_no_check_tx) {
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

	if (is_udplite)  				 /*     UDP-Lite      */
		csum = udplite_csum(skb);

	else if (sk->sk_no_check_tx) {			 /* UDP csum off */

		skb->ip_summed = CHECKSUM_NONE;
		goto send;

	} else if (skb->ip_summed == CHECKSUM_PARTIAL) { /* UDP hardware csum */
csum_partial:

		udp4_hwcsum(skb, fl4->saddr, fl4->daddr);
		goto send;

	} else
		csum = udp_csum(skb);

	/* add protocol-dependent pseudo-header */
	uh->check = csum_tcpudp_magic(fl4->saddr, fl4->daddr, len,
				      sk->sk_protocol, csum);
	if (uh->check == 0)
		uh->check = CSUM_MANGLED_0;

send:
	err = ip_send_skb(sock_net(sk), skb);
	if (err) {
		if (err == -ENOBUFS && !inet->recverr) {
			UDP_INC_STATS(sock_net(sk),
				      UDP_MIB_SNDBUFERRORS, is_udplite);
			err = 0;
		}
	} else
		UDP_INC_STATS(sock_net(sk),
			      UDP_MIB_OUTDATAGRAMS, is_udplite);
	return err;
}