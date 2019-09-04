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
struct nft_flowtable {int dummy; } ;
struct nft_ctx {TYPE_1__* table; int /*<<< orphan*/  net; } ;
struct TYPE_2__ {int /*<<< orphan*/  use; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFT_MSG_DELFLOWTABLE ; 
 int /*<<< orphan*/  nft_deactivate_next (int /*<<< orphan*/ ,struct nft_flowtable*) ; 
 int nft_trans_flowtable_add (struct nft_ctx*,int /*<<< orphan*/ ,struct nft_flowtable*) ; 

__attribute__((used)) static int nft_delflowtable(struct nft_ctx *ctx,
			    struct nft_flowtable *flowtable)
{
	int err;

	err = nft_trans_flowtable_add(ctx, NFT_MSG_DELFLOWTABLE, flowtable);
	if (err < 0)
		return err;

	nft_deactivate_next(ctx->net, flowtable);
	ctx->table->use--;

	return err;
}