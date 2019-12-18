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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nft_expr {int dummy; } ;
struct nft_dynset {scalar_t__ expr; int /*<<< orphan*/  timeout; TYPE_1__* set; int /*<<< orphan*/  op; int /*<<< orphan*/  sreg_data; int /*<<< orphan*/  sreg_key; scalar_t__ invert; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_DYNSET_EXPR ; 
 int /*<<< orphan*/  NFTA_DYNSET_FLAGS ; 
 int /*<<< orphan*/  NFTA_DYNSET_OP ; 
 int /*<<< orphan*/  NFTA_DYNSET_PAD ; 
 int /*<<< orphan*/  NFTA_DYNSET_SET_NAME ; 
 int /*<<< orphan*/  NFTA_DYNSET_SREG_DATA ; 
 int /*<<< orphan*/  NFTA_DYNSET_SREG_KEY ; 
 int /*<<< orphan*/  NFTA_DYNSET_TIMEOUT ; 
 int /*<<< orphan*/  NFT_DYNSET_F_INV ; 
 int NFT_SET_MAP ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 scalar_t__ nft_dump_register (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nft_expr_dump (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct nft_dynset* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be64 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_dynset_dump(struct sk_buff *skb, const struct nft_expr *expr)
{
	const struct nft_dynset *priv = nft_expr_priv(expr);
	u32 flags = priv->invert ? NFT_DYNSET_F_INV : 0;

	if (nft_dump_register(skb, NFTA_DYNSET_SREG_KEY, priv->sreg_key))
		goto nla_put_failure;
	if (priv->set->flags & NFT_SET_MAP &&
	    nft_dump_register(skb, NFTA_DYNSET_SREG_DATA, priv->sreg_data))
		goto nla_put_failure;
	if (nla_put_be32(skb, NFTA_DYNSET_OP, htonl(priv->op)))
		goto nla_put_failure;
	if (nla_put_string(skb, NFTA_DYNSET_SET_NAME, priv->set->name))
		goto nla_put_failure;
	if (nla_put_be64(skb, NFTA_DYNSET_TIMEOUT,
			 cpu_to_be64(jiffies_to_msecs(priv->timeout)),
			 NFTA_DYNSET_PAD))
		goto nla_put_failure;
	if (priv->expr && nft_expr_dump(skb, NFTA_DYNSET_EXPR, priv->expr))
		goto nla_put_failure;
	if (nla_put_be32(skb, NFTA_DYNSET_FLAGS, htonl(flags)))
		goto nla_put_failure;
	return 0;

nla_put_failure:
	return -1;
}