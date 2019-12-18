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
struct nft_xfrm {int dir; } ;
struct TYPE_2__ {int /*<<< orphan*/  code; } ;
struct nft_regs {TYPE_1__ verdict; } ;
struct nft_pktinfo {int dummy; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFT_BREAK ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
#define  XFRM_POLICY_IN 129 
#define  XFRM_POLICY_OUT 128 
 struct nft_xfrm* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_xfrm_get_eval_in (struct nft_xfrm const*,struct nft_regs*,struct nft_pktinfo const*) ; 
 int /*<<< orphan*/  nft_xfrm_get_eval_out (struct nft_xfrm const*,struct nft_regs*,struct nft_pktinfo const*) ; 

__attribute__((used)) static void nft_xfrm_get_eval(const struct nft_expr *expr,
			      struct nft_regs *regs,
			      const struct nft_pktinfo *pkt)
{
	const struct nft_xfrm *priv = nft_expr_priv(expr);

	switch (priv->dir) {
	case XFRM_POLICY_IN:
		nft_xfrm_get_eval_in(priv, regs, pkt);
		break;
	case XFRM_POLICY_OUT:
		nft_xfrm_get_eval_out(priv, regs, pkt);
		break;
	default:
		WARN_ON_ONCE(1);
		regs->verdict.code = NFT_BREAK;
		break;
	}
}