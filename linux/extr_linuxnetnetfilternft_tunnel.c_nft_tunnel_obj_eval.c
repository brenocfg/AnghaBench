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
struct sk_buff {int dummy; } ;
struct nft_tunnel_obj {scalar_t__ md; } ;
struct nft_regs {int dummy; } ;
struct nft_pktinfo {struct sk_buff* skb; } ;
struct nft_object {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_hold (struct dst_entry*) ; 
 struct nft_tunnel_obj* nft_obj_data (struct nft_object*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,struct dst_entry*) ; 

__attribute__((used)) static inline void nft_tunnel_obj_eval(struct nft_object *obj,
				       struct nft_regs *regs,
				       const struct nft_pktinfo *pkt)
{
	struct nft_tunnel_obj *priv = nft_obj_data(obj);
	struct sk_buff *skb = pkt->skb;

	skb_dst_drop(skb);
	dst_hold((struct dst_entry *) priv->md);
	skb_dst_set(skb, (struct dst_entry *) priv->md);
}