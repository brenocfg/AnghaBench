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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct nft_regs {scalar_t__* data; } ;
struct TYPE_2__ {int thoff; } ;
struct nft_pktinfo {TYPE_1__ xt; int /*<<< orphan*/  tprot_set; struct sk_buff* skb; } ;
struct nft_payload {size_t dreg; scalar_t__ base; int len; int /*<<< orphan*/  offset; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 scalar_t__ NFT_PAYLOAD_NETWORK_HEADER ; 
 struct nft_payload* nft_expr_priv (struct nft_expr const*) ; 
 unsigned char* skb_network_header (struct sk_buff const*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool nft_payload_fast_eval(const struct nft_expr *expr,
				  struct nft_regs *regs,
				  const struct nft_pktinfo *pkt)
{
	const struct nft_payload *priv = nft_expr_priv(expr);
	const struct sk_buff *skb = pkt->skb;
	u32 *dest = &regs->data[priv->dreg];
	unsigned char *ptr;

	if (priv->base == NFT_PAYLOAD_NETWORK_HEADER)
		ptr = skb_network_header(skb);
	else {
		if (!pkt->tprot_set)
			return false;
		ptr = skb_network_header(skb) + pkt->xt.thoff;
	}

	ptr += priv->offset;

	if (unlikely(ptr + priv->len > skb_tail_pointer(skb)))
		return false;

	*dest = 0;
	if (priv->len == 2)
		*(u16 *)dest = *(u16 *)ptr;
	else if (priv->len == 4)
		*(u32 *)dest = *(u32 *)ptr;
	else
		*(u8 *)dest = *(u8 *)ptr;
	return true;
}