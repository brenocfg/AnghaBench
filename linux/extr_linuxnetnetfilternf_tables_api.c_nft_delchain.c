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
struct nft_ctx {int /*<<< orphan*/  chain; int /*<<< orphan*/  net; TYPE_1__* table; } ;
struct TYPE_2__ {int /*<<< orphan*/  use; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFT_MSG_DELCHAIN ; 
 int /*<<< orphan*/  nft_deactivate_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nft_trans_chain_add (struct nft_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_delchain(struct nft_ctx *ctx)
{
	int err;

	err = nft_trans_chain_add(ctx, NFT_MSG_DELCHAIN);
	if (err < 0)
		return err;

	ctx->table->use--;
	nft_deactivate_next(ctx->net, ctx->chain);

	return err;
}