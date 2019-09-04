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
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct nft_symhash {size_t dreg; scalar_t__ offset; int /*<<< orphan*/  modulus; struct nft_set* map; } ;
struct nft_set_ext {int dummy; } ;
struct nft_set {int /*<<< orphan*/  dlen; TYPE_1__* ops; } ;
struct nft_regs {int /*<<< orphan*/ * data; } ;
struct nft_pktinfo {struct sk_buff* skb; } ;
struct nft_expr {int dummy; } ;
struct TYPE_2__ {int (* lookup ) (int /*<<< orphan*/ ,struct nft_set const*,scalar_t__*,struct nft_set_ext const**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_get_hash_symmetric (struct sk_buff*) ; 
 int /*<<< orphan*/  nft_data_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_symhash* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_net (struct nft_pktinfo const*) ; 
 int /*<<< orphan*/  nft_set_ext_data (struct nft_set_ext const*) ; 
 scalar_t__ reciprocal_scale (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,struct nft_set const*,scalar_t__*,struct nft_set_ext const**) ; 

__attribute__((used)) static void nft_symhash_map_eval(const struct nft_expr *expr,
				 struct nft_regs *regs,
				 const struct nft_pktinfo *pkt)
{
	struct nft_symhash *priv = nft_expr_priv(expr);
	struct sk_buff *skb = pkt->skb;
	const struct nft_set *map = priv->map;
	const struct nft_set_ext *ext;
	u32 result;
	bool found;

	result = reciprocal_scale(__skb_get_hash_symmetric(skb),
				  priv->modulus) + priv->offset;

	found = map->ops->lookup(nft_net(pkt), map, &result, &ext);
	if (!found)
		return;

	nft_data_copy(&regs->data[priv->dreg],
		      nft_set_ext_data(ext), map->dlen);
}