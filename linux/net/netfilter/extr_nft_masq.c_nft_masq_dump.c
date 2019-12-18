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
struct nft_masq {scalar_t__ flags; scalar_t__ sreg_proto_max; scalar_t__ sreg_proto_min; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_MASQ_FLAGS ; 
 int /*<<< orphan*/  NFTA_MASQ_REG_PROTO_MAX ; 
 int /*<<< orphan*/  NFTA_MASQ_REG_PROTO_MIN ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 scalar_t__ nft_dump_register (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct nft_masq* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_masq_dump(struct sk_buff *skb, const struct nft_expr *expr)
{
	const struct nft_masq *priv = nft_expr_priv(expr);

	if (priv->flags != 0 &&
	    nla_put_be32(skb, NFTA_MASQ_FLAGS, htonl(priv->flags)))
		goto nla_put_failure;

	if (priv->sreg_proto_min) {
		if (nft_dump_register(skb, NFTA_MASQ_REG_PROTO_MIN,
				      priv->sreg_proto_min) ||
		    nft_dump_register(skb, NFTA_MASQ_REG_PROTO_MAX,
				      priv->sreg_proto_max))
			goto nla_put_failure;
	}

	return 0;

nla_put_failure:
	return -1;
}