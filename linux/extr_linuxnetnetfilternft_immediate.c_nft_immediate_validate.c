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
struct TYPE_2__ {int code; int /*<<< orphan*/  chain; } ;
struct nft_data {TYPE_1__ verdict; } ;
struct nft_immediate_expr {scalar_t__ dreg; struct nft_data data; } ;
struct nft_expr {int dummy; } ;
struct nft_ctx {int /*<<< orphan*/  level; } ;

/* Variables and functions */
#define  NFT_GOTO 129 
#define  NFT_JUMP 128 
 scalar_t__ NFT_REG_VERDICT ; 
 int nft_chain_validate (struct nft_ctx const*,int /*<<< orphan*/ ) ; 
 struct nft_immediate_expr* nft_expr_priv (struct nft_expr const*) ; 

__attribute__((used)) static int nft_immediate_validate(const struct nft_ctx *ctx,
				  const struct nft_expr *expr,
				  const struct nft_data **d)
{
	const struct nft_immediate_expr *priv = nft_expr_priv(expr);
	struct nft_ctx *pctx = (struct nft_ctx *)ctx;
	const struct nft_data *data;
	int err;

	if (priv->dreg != NFT_REG_VERDICT)
		return 0;

	data = &priv->data;

	switch (data->verdict.code) {
	case NFT_JUMP:
	case NFT_GOTO:
		pctx->level++;
		err = nft_chain_validate(ctx, data->verdict.chain);
		if (err < 0)
			return err;
		pctx->level--;
		break;
	default:
		break;
	}

	return 0;
}