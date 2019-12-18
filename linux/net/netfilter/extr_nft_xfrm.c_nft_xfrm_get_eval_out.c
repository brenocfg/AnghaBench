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
struct xfrm_dst {struct dst_entry* child; } ;
struct nft_xfrm {int spnum; } ;
struct TYPE_2__ {int /*<<< orphan*/  code; } ;
struct nft_regs {TYPE_1__ verdict; } ;
struct nft_pktinfo {int /*<<< orphan*/  skb; } ;
struct dst_entry {scalar_t__ xfrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFT_BREAK ; 
 int /*<<< orphan*/  nft_xfrm_state_get_key (struct nft_xfrm const*,struct nft_regs*,scalar_t__) ; 
 struct dst_entry* skb_dst (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nft_xfrm_get_eval_out(const struct nft_xfrm *priv,
				  struct nft_regs *regs,
				  const struct nft_pktinfo *pkt)
{
	const struct dst_entry *dst = skb_dst(pkt->skb);
	int i;

	for (i = 0; dst && dst->xfrm;
	     dst = ((const struct xfrm_dst *)dst)->child, i++) {
		if (i < priv->spnum)
			continue;

		nft_xfrm_state_get_key(priv, regs, dst->xfrm);
		return;
	}

	regs->verdict.code = NFT_BREAK;
}