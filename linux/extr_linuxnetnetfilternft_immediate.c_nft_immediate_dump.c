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
struct nft_immediate_expr {int /*<<< orphan*/  dlen; int /*<<< orphan*/  dreg; int /*<<< orphan*/  data; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_IMMEDIATE_DATA ; 
 int /*<<< orphan*/  NFTA_IMMEDIATE_DREG ; 
 int nft_data_dump (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nft_dreg_to_type (int /*<<< orphan*/ ) ; 
 scalar_t__ nft_dump_register (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_immediate_expr* nft_expr_priv (struct nft_expr const*) ; 

__attribute__((used)) static int nft_immediate_dump(struct sk_buff *skb, const struct nft_expr *expr)
{
	const struct nft_immediate_expr *priv = nft_expr_priv(expr);

	if (nft_dump_register(skb, NFTA_IMMEDIATE_DREG, priv->dreg))
		goto nla_put_failure;

	return nft_data_dump(skb, NFTA_IMMEDIATE_DATA, &priv->data,
			     nft_dreg_to_type(priv->dreg), priv->dlen);

nla_put_failure:
	return -1;
}