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
struct nft_reject {int type; int /*<<< orphan*/  icmp_code; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_REJECT_ICMP_CODE ; 
 int /*<<< orphan*/  NFTA_REJECT_TYPE ; 
#define  NFT_REJECT_ICMPX_UNREACH 129 
#define  NFT_REJECT_ICMP_UNREACH 128 
 int /*<<< orphan*/  htonl (int) ; 
 struct nft_reject* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_reject_bridge_dump(struct sk_buff *skb,
				  const struct nft_expr *expr)
{
	const struct nft_reject *priv = nft_expr_priv(expr);

	if (nla_put_be32(skb, NFTA_REJECT_TYPE, htonl(priv->type)))
		goto nla_put_failure;

	switch (priv->type) {
	case NFT_REJECT_ICMP_UNREACH:
	case NFT_REJECT_ICMPX_UNREACH:
		if (nla_put_u8(skb, NFTA_REJECT_ICMP_CODE, priv->icmp_code))
			goto nla_put_failure;
		break;
	default:
		break;
	}

	return 0;

nla_put_failure:
	return -1;
}