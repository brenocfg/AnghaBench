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
struct sk_buff {int dummy; } ;
struct nft_jhash {TYPE_1__* map; } ;
struct nft_expr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_HASH_SET_NAME ; 
 struct nft_jhash* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nft_jhash_dump (struct sk_buff*,struct nft_expr const*) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_jhash_map_dump(struct sk_buff *skb,
			       const struct nft_expr *expr)
{
	const struct nft_jhash *priv = nft_expr_priv(expr);

	if (nft_jhash_dump(skb, expr) ||
	    nla_put_string(skb, NFTA_HASH_SET_NAME, priv->map->name))
		return -1;

	return 0;
}