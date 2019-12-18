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
struct nft_pktinfo {int dummy; } ;
struct nft_object {int dummy; } ;
struct nft_limit_pkts {int /*<<< orphan*/  cost; int /*<<< orphan*/  limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFT_BREAK ; 
 scalar_t__ nft_limit_eval (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nft_limit_pkts* nft_obj_data (struct nft_object*) ; 

__attribute__((used)) static void nft_limit_obj_pkts_eval(struct nft_object *obj,
				    struct nft_regs *regs,
				    const struct nft_pktinfo *pkt)
{
	struct nft_limit_pkts *priv = nft_obj_data(obj);

	if (nft_limit_eval(&priv->limit, priv->cost))
		regs->verdict.code = NFT_BREAK;
}