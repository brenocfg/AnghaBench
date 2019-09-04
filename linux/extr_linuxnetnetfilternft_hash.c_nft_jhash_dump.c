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
struct nft_jhash {scalar_t__ len; scalar_t__ modulus; scalar_t__ seed; scalar_t__ offset; int /*<<< orphan*/  autogen_seed; int /*<<< orphan*/  dreg; int /*<<< orphan*/  sreg; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_HASH_DREG ; 
 int /*<<< orphan*/  NFTA_HASH_LEN ; 
 int /*<<< orphan*/  NFTA_HASH_MODULUS ; 
 int /*<<< orphan*/  NFTA_HASH_OFFSET ; 
 int /*<<< orphan*/  NFTA_HASH_SEED ; 
 int /*<<< orphan*/  NFTA_HASH_SREG ; 
 int /*<<< orphan*/  NFTA_HASH_TYPE ; 
 scalar_t__ NFT_HASH_JENKINS ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 scalar_t__ nft_dump_register (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_jhash* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_jhash_dump(struct sk_buff *skb,
			  const struct nft_expr *expr)
{
	const struct nft_jhash *priv = nft_expr_priv(expr);

	if (nft_dump_register(skb, NFTA_HASH_SREG, priv->sreg))
		goto nla_put_failure;
	if (nft_dump_register(skb, NFTA_HASH_DREG, priv->dreg))
		goto nla_put_failure;
	if (nla_put_be32(skb, NFTA_HASH_LEN, htonl(priv->len)))
		goto nla_put_failure;
	if (nla_put_be32(skb, NFTA_HASH_MODULUS, htonl(priv->modulus)))
		goto nla_put_failure;
	if (!priv->autogen_seed &&
	    nla_put_be32(skb, NFTA_HASH_SEED, htonl(priv->seed)))
		goto nla_put_failure;
	if (priv->offset != 0)
		if (nla_put_be32(skb, NFTA_HASH_OFFSET, htonl(priv->offset)))
			goto nla_put_failure;
	if (nla_put_be32(skb, NFTA_HASH_TYPE, htonl(NFT_HASH_JENKINS)))
		goto nla_put_failure;
	return 0;

nla_put_failure:
	return -1;
}