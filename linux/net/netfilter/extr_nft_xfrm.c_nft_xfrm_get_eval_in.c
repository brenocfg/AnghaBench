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
struct xfrm_state {int dummy; } ;
struct sec_path {size_t len; struct xfrm_state** xvec; } ;
struct nft_xfrm {size_t spnum; } ;
struct TYPE_2__ {int /*<<< orphan*/  code; } ;
struct nft_regs {TYPE_1__ verdict; } ;
struct nft_pktinfo {int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFT_BREAK ; 
 int /*<<< orphan*/  nft_xfrm_state_get_key (struct nft_xfrm const*,struct nft_regs*,struct xfrm_state const*) ; 
 struct sec_path* skb_sec_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nft_xfrm_get_eval_in(const struct nft_xfrm *priv,
				    struct nft_regs *regs,
				    const struct nft_pktinfo *pkt)
{
	const struct sec_path *sp = skb_sec_path(pkt->skb);
	const struct xfrm_state *state;

	if (sp == NULL || sp->len <= priv->spnum) {
		regs->verdict.code = NFT_BREAK;
		return;
	}

	state = sp->xvec[priv->spnum];
	nft_xfrm_state_get_key(priv, regs, state);
}