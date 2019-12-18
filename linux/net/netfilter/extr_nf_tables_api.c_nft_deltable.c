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
struct nft_ctx {int /*<<< orphan*/  table; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFT_MSG_DELTABLE ; 
 int /*<<< orphan*/  nft_deactivate_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nft_trans_table_add (struct nft_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_deltable(struct nft_ctx *ctx)
{
	int err;

	err = nft_trans_table_add(ctx, NFT_MSG_DELTABLE);
	if (err < 0)
		return err;

	nft_deactivate_next(ctx->net, ctx->table);
	return err;
}