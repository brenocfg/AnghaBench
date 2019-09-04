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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct genevehdr {scalar_t__ ver; scalar_t__ proto_type; int opt_len; } ;
struct geneve_sock {int dummy; } ;
struct geneve_dev {TYPE_2__* dev; int /*<<< orphan*/  net; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_dropped; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_TEB ; 
 scalar_t__ GENEVE_BASE_HLEN ; 
 scalar_t__ GENEVE_VER ; 
 int /*<<< orphan*/  dev_net (TYPE_2__*) ; 
 struct genevehdr* geneve_hdr (struct sk_buff*) ; 
 struct geneve_dev* geneve_lookup_skb (struct geneve_sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  geneve_rx (struct geneve_dev*,struct geneve_sock*,struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 scalar_t__ iptunnel_pull_header (struct sk_buff*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,scalar_t__) ; 
 struct geneve_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int geneve_udp_encap_recv(struct sock *sk, struct sk_buff *skb)
{
	struct genevehdr *geneveh;
	struct geneve_dev *geneve;
	struct geneve_sock *gs;
	int opts_len;

	/* Need UDP and Geneve header to be present */
	if (unlikely(!pskb_may_pull(skb, GENEVE_BASE_HLEN)))
		goto drop;

	/* Return packets with reserved bits set */
	geneveh = geneve_hdr(skb);
	if (unlikely(geneveh->ver != GENEVE_VER))
		goto drop;

	if (unlikely(geneveh->proto_type != htons(ETH_P_TEB)))
		goto drop;

	gs = rcu_dereference_sk_user_data(sk);
	if (!gs)
		goto drop;

	geneve = geneve_lookup_skb(gs, skb);
	if (!geneve)
		goto drop;

	opts_len = geneveh->opt_len * 4;
	if (iptunnel_pull_header(skb, GENEVE_BASE_HLEN + opts_len,
				 htons(ETH_P_TEB),
				 !net_eq(geneve->net, dev_net(geneve->dev)))) {
		geneve->dev->stats.rx_dropped++;
		goto drop;
	}

	geneve_rx(geneve, gs, skb);
	return 0;

drop:
	/* Consume bad packet */
	kfree_skb(skb);
	return 0;
}