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
struct nft_payload_set {int /*<<< orphan*/  csum_flags; int /*<<< orphan*/  csum_offset; int /*<<< orphan*/  csum_type; int /*<<< orphan*/  len; int /*<<< orphan*/  offset; int /*<<< orphan*/  base; int /*<<< orphan*/  sreg; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_PAYLOAD_BASE ; 
 int /*<<< orphan*/  NFTA_PAYLOAD_CSUM_FLAGS ; 
 int /*<<< orphan*/  NFTA_PAYLOAD_CSUM_OFFSET ; 
 int /*<<< orphan*/  NFTA_PAYLOAD_CSUM_TYPE ; 
 int /*<<< orphan*/  NFTA_PAYLOAD_LEN ; 
 int /*<<< orphan*/  NFTA_PAYLOAD_OFFSET ; 
 int /*<<< orphan*/  NFTA_PAYLOAD_SREG ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ nft_dump_register (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_payload_set* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_payload_set_dump(struct sk_buff *skb, const struct nft_expr *expr)
{
	const struct nft_payload_set *priv = nft_expr_priv(expr);

	if (nft_dump_register(skb, NFTA_PAYLOAD_SREG, priv->sreg) ||
	    nla_put_be32(skb, NFTA_PAYLOAD_BASE, htonl(priv->base)) ||
	    nla_put_be32(skb, NFTA_PAYLOAD_OFFSET, htonl(priv->offset)) ||
	    nla_put_be32(skb, NFTA_PAYLOAD_LEN, htonl(priv->len)) ||
	    nla_put_be32(skb, NFTA_PAYLOAD_CSUM_TYPE, htonl(priv->csum_type)) ||
	    nla_put_be32(skb, NFTA_PAYLOAD_CSUM_OFFSET,
			 htonl(priv->csum_offset)) ||
	    nla_put_be32(skb, NFTA_PAYLOAD_CSUM_FLAGS, htonl(priv->csum_flags)))
		goto nla_put_failure;
	return 0;

nla_put_failure:
	return -1;
}