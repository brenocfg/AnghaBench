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
struct nft_exthdr {int /*<<< orphan*/  op; int /*<<< orphan*/  flags; int /*<<< orphan*/  len; int /*<<< orphan*/  offset; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_EXTHDR_FLAGS ; 
 int /*<<< orphan*/  NFTA_EXTHDR_LEN ; 
 int /*<<< orphan*/  NFTA_EXTHDR_OFFSET ; 
 int /*<<< orphan*/  NFTA_EXTHDR_OP ; 
 int /*<<< orphan*/  NFTA_EXTHDR_TYPE ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_exthdr_dump_common(struct sk_buff *skb, const struct nft_exthdr *priv)
{
	if (nla_put_u8(skb, NFTA_EXTHDR_TYPE, priv->type))
		goto nla_put_failure;
	if (nla_put_be32(skb, NFTA_EXTHDR_OFFSET, htonl(priv->offset)))
		goto nla_put_failure;
	if (nla_put_be32(skb, NFTA_EXTHDR_LEN, htonl(priv->len)))
		goto nla_put_failure;
	if (nla_put_be32(skb, NFTA_EXTHDR_FLAGS, htonl(priv->flags)))
		goto nla_put_failure;
	if (nla_put_be32(skb, NFTA_EXTHDR_OP, htonl(priv->op)))
		goto nla_put_failure;
	return 0;

nla_put_failure:
	return -1;
}