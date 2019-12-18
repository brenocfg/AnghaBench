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
struct nft_nat {int type; scalar_t__ family; scalar_t__ flags; scalar_t__ sreg_proto_max; scalar_t__ sreg_proto_min; scalar_t__ sreg_addr_max; scalar_t__ sreg_addr_min; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_NAT_FAMILY ; 
 int /*<<< orphan*/  NFTA_NAT_FLAGS ; 
 int /*<<< orphan*/  NFTA_NAT_REG_ADDR_MAX ; 
 int /*<<< orphan*/  NFTA_NAT_REG_ADDR_MIN ; 
 int /*<<< orphan*/  NFTA_NAT_REG_PROTO_MAX ; 
 int /*<<< orphan*/  NFTA_NAT_REG_PROTO_MIN ; 
 int /*<<< orphan*/  NFTA_NAT_TYPE ; 
 scalar_t__ NFT_NAT_DNAT ; 
 scalar_t__ NFT_NAT_SNAT ; 
#define  NF_NAT_MANIP_DST 129 
#define  NF_NAT_MANIP_SRC 128 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 scalar_t__ nft_dump_register (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct nft_nat* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_nat_dump(struct sk_buff *skb, const struct nft_expr *expr)
{
	const struct nft_nat *priv = nft_expr_priv(expr);

	switch (priv->type) {
	case NF_NAT_MANIP_SRC:
		if (nla_put_be32(skb, NFTA_NAT_TYPE, htonl(NFT_NAT_SNAT)))
			goto nla_put_failure;
		break;
	case NF_NAT_MANIP_DST:
		if (nla_put_be32(skb, NFTA_NAT_TYPE, htonl(NFT_NAT_DNAT)))
			goto nla_put_failure;
		break;
	}

	if (nla_put_be32(skb, NFTA_NAT_FAMILY, htonl(priv->family)))
		goto nla_put_failure;

	if (priv->sreg_addr_min) {
		if (nft_dump_register(skb, NFTA_NAT_REG_ADDR_MIN,
				      priv->sreg_addr_min) ||
		    nft_dump_register(skb, NFTA_NAT_REG_ADDR_MAX,
				      priv->sreg_addr_max))
			goto nla_put_failure;
	}

	if (priv->sreg_proto_min) {
		if (nft_dump_register(skb, NFTA_NAT_REG_PROTO_MIN,
				      priv->sreg_proto_min) ||
		    nft_dump_register(skb, NFTA_NAT_REG_PROTO_MAX,
				      priv->sreg_proto_max))
			goto nla_put_failure;
	}

	if (priv->flags != 0) {
		if (nla_put_be32(skb, NFTA_NAT_FLAGS, htonl(priv->flags)))
			goto nla_put_failure;
	}

	return 0;

nla_put_failure:
	return -1;
}