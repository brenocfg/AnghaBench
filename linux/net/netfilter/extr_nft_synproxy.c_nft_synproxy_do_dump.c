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
struct TYPE_2__ {int /*<<< orphan*/  options; int /*<<< orphan*/  wscale; int /*<<< orphan*/  mss; } ;
struct nft_synproxy {TYPE_1__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_SYNPROXY_FLAGS ; 
 int /*<<< orphan*/  NFTA_SYNPROXY_MSS ; 
 int /*<<< orphan*/  NFTA_SYNPROXY_WSCALE ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_synproxy_do_dump(struct sk_buff *skb, struct nft_synproxy *priv)
{
	if (nla_put_be16(skb, NFTA_SYNPROXY_MSS, htons(priv->info.mss)) ||
	    nla_put_u8(skb, NFTA_SYNPROXY_WSCALE, priv->info.wscale) ||
	    nla_put_be32(skb, NFTA_SYNPROXY_FLAGS, htonl(priv->info.options)))
		goto nla_put_failure;

	return 0;

nla_put_failure:
	return -1;
}