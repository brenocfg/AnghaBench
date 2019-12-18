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
struct nft_set_ext {int dummy; } ;
struct nft_set {int flags; int /*<<< orphan*/  dlen; TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  code; } ;
struct nft_regs {int /*<<< orphan*/ * data; TYPE_2__ verdict; } ;
struct nft_pktinfo {int dummy; } ;
struct nft_lookup {size_t sreg; int invert; size_t dreg; struct nft_set* set; } ;
struct nft_expr {int dummy; } ;
struct TYPE_3__ {int (* lookup ) (int /*<<< orphan*/ ,struct nft_set const*,int /*<<< orphan*/ *,struct nft_set_ext const**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NFT_BREAK ; 
 int NFT_SET_MAP ; 
 int /*<<< orphan*/  nft_data_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_lookup* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_net (struct nft_pktinfo const*) ; 
 int /*<<< orphan*/  nft_set_ext_data (struct nft_set_ext const*) ; 
 int stub1 (int /*<<< orphan*/ ,struct nft_set const*,int /*<<< orphan*/ *,struct nft_set_ext const**) ; 

void nft_lookup_eval(const struct nft_expr *expr,
		     struct nft_regs *regs,
		     const struct nft_pktinfo *pkt)
{
	const struct nft_lookup *priv = nft_expr_priv(expr);
	const struct nft_set *set = priv->set;
	const struct nft_set_ext *ext;
	bool found;

	found = set->ops->lookup(nft_net(pkt), set, &regs->data[priv->sreg],
				 &ext) ^ priv->invert;
	if (!found) {
		regs->verdict.code = NFT_BREAK;
		return;
	}

	if (set->flags & NFT_SET_MAP)
		nft_data_copy(&regs->data[priv->dreg],
			      nft_set_ext_data(ext), set->dlen);

}