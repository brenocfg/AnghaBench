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
typedef  scalar_t__ u32 ;
struct sk_buff {int data; } ;
struct TYPE_4__ {int /*<<< orphan*/  code; } ;
struct nft_regs {TYPE_2__ verdict; scalar_t__* data; } ;
struct TYPE_3__ {int thoff; } ;
struct nft_pktinfo {TYPE_1__ xt; int /*<<< orphan*/  tprot_set; struct sk_buff* skb; } ;
struct nft_payload {size_t dreg; size_t len; int base; int offset; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  NFT_BREAK ; 
#define  NFT_PAYLOAD_LL_HEADER 130 
#define  NFT_PAYLOAD_NETWORK_HEADER 129 
#define  NFT_PAYLOAD_TRANSPORT_HEADER 128 
 size_t NFT_REG32_SIZE ; 
 struct nft_payload* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_payload_copy_vlan (scalar_t__*,struct sk_buff const*,int,size_t) ; 
 scalar_t__ skb_copy_bits (struct sk_buff const*,int,scalar_t__*,size_t) ; 
 int skb_mac_header (struct sk_buff const*) ; 
 int /*<<< orphan*/  skb_mac_header_was_set (struct sk_buff const*) ; 
 int skb_network_offset (struct sk_buff const*) ; 
 int /*<<< orphan*/  skb_vlan_tag_present (struct sk_buff const*) ; 

void nft_payload_eval(const struct nft_expr *expr,
		      struct nft_regs *regs,
		      const struct nft_pktinfo *pkt)
{
	const struct nft_payload *priv = nft_expr_priv(expr);
	const struct sk_buff *skb = pkt->skb;
	u32 *dest = &regs->data[priv->dreg];
	int offset;

	dest[priv->len / NFT_REG32_SIZE] = 0;
	switch (priv->base) {
	case NFT_PAYLOAD_LL_HEADER:
		if (!skb_mac_header_was_set(skb))
			goto err;

		if (skb_vlan_tag_present(skb)) {
			if (!nft_payload_copy_vlan(dest, skb,
						   priv->offset, priv->len))
				goto err;
			return;
		}
		offset = skb_mac_header(skb) - skb->data;
		break;
	case NFT_PAYLOAD_NETWORK_HEADER:
		offset = skb_network_offset(skb);
		break;
	case NFT_PAYLOAD_TRANSPORT_HEADER:
		if (!pkt->tprot_set)
			goto err;
		offset = pkt->xt.thoff;
		break;
	default:
		BUG();
	}
	offset += priv->offset;

	if (skb_copy_bits(skb, offset, dest, priv->len) < 0)
		goto err;
	return;
err:
	regs->verdict.code = NFT_BREAK;
}