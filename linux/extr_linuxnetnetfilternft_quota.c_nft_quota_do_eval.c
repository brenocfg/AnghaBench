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
struct TYPE_2__ {int /*<<< orphan*/  code; } ;
struct nft_regs {TYPE_1__ verdict; } ;
struct nft_quota {int dummy; } ;
struct nft_pktinfo {int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFT_BREAK ; 
 int nft_overquota (struct nft_quota*,int /*<<< orphan*/ ) ; 
 int nft_quota_invert (struct nft_quota*) ; 

__attribute__((used)) static inline void nft_quota_do_eval(struct nft_quota *priv,
				     struct nft_regs *regs,
				     const struct nft_pktinfo *pkt)
{
	if (nft_overquota(priv, pkt->skb) ^ nft_quota_invert(priv))
		regs->verdict.code = NFT_BREAK;
}