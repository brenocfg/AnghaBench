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
struct nft_immediate_expr {int /*<<< orphan*/  dreg; int /*<<< orphan*/  data; } ;
struct nft_expr {int dummy; } ;
struct nft_ctx {int dummy; } ;
typedef  enum nft_trans_phase { ____Placeholder_nft_trans_phase } nft_trans_phase ;

/* Variables and functions */
 int NFT_TRANS_COMMIT ; 
 void nft_data_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nft_dreg_to_type (int /*<<< orphan*/ ) ; 
 struct nft_immediate_expr* nft_expr_priv (struct nft_expr const*) ; 

__attribute__((used)) static void nft_immediate_deactivate(const struct nft_ctx *ctx,
				     const struct nft_expr *expr,
				     enum nft_trans_phase phase)
{
	const struct nft_immediate_expr *priv = nft_expr_priv(expr);

	if (phase == NFT_TRANS_COMMIT)
		return;

	return nft_data_release(&priv->data, nft_dreg_to_type(priv->dreg));
}