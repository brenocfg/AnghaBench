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
struct nft_trans {int dummy; } ;
struct nft_ctx {int /*<<< orphan*/  chain; int /*<<< orphan*/  net; TYPE_1__* table; } ;
struct TYPE_2__ {int /*<<< orphan*/  use; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nft_trans*) ; 
 int /*<<< orphan*/  NFT_MSG_DELCHAIN ; 
 int PTR_ERR (struct nft_trans*) ; 
 int /*<<< orphan*/  nft_deactivate_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_trans* nft_trans_chain_add (struct nft_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_delchain(struct nft_ctx *ctx)
{
	struct nft_trans *trans;

	trans = nft_trans_chain_add(ctx, NFT_MSG_DELCHAIN);
	if (IS_ERR(trans))
		return PTR_ERR(trans);

	ctx->table->use--;
	nft_deactivate_next(ctx->net, ctx->chain);

	return 0;
}