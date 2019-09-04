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
struct nft_connlimit {scalar_t__ invert; int /*<<< orphan*/  limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_CONNLIMIT_COUNT ; 
 int /*<<< orphan*/  NFTA_CONNLIMIT_FLAGS ; 
 int /*<<< orphan*/  NFT_CONNLIMIT_F_INV ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_connlimit_do_dump(struct sk_buff *skb,
				 struct nft_connlimit *priv)
{
	if (nla_put_be32(skb, NFTA_CONNLIMIT_COUNT, htonl(priv->limit)))
		goto nla_put_failure;
	if (priv->invert &&
	    nla_put_be32(skb, NFTA_CONNLIMIT_FLAGS, htonl(NFT_CONNLIMIT_F_INV)))
		goto nla_put_failure;

	return 0;

nla_put_failure:
	return -1;
}