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
struct nft_objref_map {TYPE_1__* set; int /*<<< orphan*/  sreg; } ;
struct nft_expr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_OBJREF_SET_NAME ; 
 int /*<<< orphan*/  NFTA_OBJREF_SET_SREG ; 
 scalar_t__ nft_dump_register (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_objref_map* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_objref_map_dump(struct sk_buff *skb, const struct nft_expr *expr)
{
	const struct nft_objref_map *priv = nft_expr_priv(expr);

	if (nft_dump_register(skb, NFTA_OBJREF_SET_SREG, priv->sreg) ||
	    nla_put_string(skb, NFTA_OBJREF_SET_NAME, priv->set->name))
		goto nla_put_failure;

	return 0;

nla_put_failure:
	return -1;
}