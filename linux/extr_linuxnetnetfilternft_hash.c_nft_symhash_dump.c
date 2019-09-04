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
struct nft_symhash {scalar_t__ modulus; scalar_t__ offset; int /*<<< orphan*/  dreg; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_HASH_DREG ; 
 int /*<<< orphan*/  NFTA_HASH_MODULUS ; 
 int /*<<< orphan*/  NFTA_HASH_OFFSET ; 
 int /*<<< orphan*/  NFTA_HASH_TYPE ; 
 scalar_t__ NFT_HASH_SYM ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 scalar_t__ nft_dump_register (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_symhash* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_symhash_dump(struct sk_buff *skb,
			    const struct nft_expr *expr)
{
	const struct nft_symhash *priv = nft_expr_priv(expr);

	if (nft_dump_register(skb, NFTA_HASH_DREG, priv->dreg))
		goto nla_put_failure;
	if (nla_put_be32(skb, NFTA_HASH_MODULUS, htonl(priv->modulus)))
		goto nla_put_failure;
	if (priv->offset != 0)
		if (nla_put_be32(skb, NFTA_HASH_OFFSET, htonl(priv->offset)))
			goto nla_put_failure;
	if (nla_put_be32(skb, NFTA_HASH_TYPE, htonl(NFT_HASH_SYM)))
		goto nla_put_failure;
	return 0;

nla_put_failure:
	return -1;
}