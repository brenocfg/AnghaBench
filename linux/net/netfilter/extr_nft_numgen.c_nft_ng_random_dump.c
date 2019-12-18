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
struct nft_ng_random {int /*<<< orphan*/  offset; int /*<<< orphan*/  modulus; int /*<<< orphan*/  dreg; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFT_NG_RANDOM ; 
 struct nft_ng_random* nft_expr_priv (struct nft_expr const*) ; 
 int nft_ng_dump (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_ng_random_dump(struct sk_buff *skb, const struct nft_expr *expr)
{
	const struct nft_ng_random *priv = nft_expr_priv(expr);

	return nft_ng_dump(skb, priv->dreg, priv->modulus, NFT_NG_RANDOM,
			   priv->offset);
}