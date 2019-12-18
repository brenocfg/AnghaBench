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
struct nlattr {int dummy; } ;
struct nft_immediate_expr {int /*<<< orphan*/  data; int /*<<< orphan*/  dreg; int /*<<< orphan*/  dlen; } ;
struct nft_expr {int dummy; } ;
struct nft_data_desc {int /*<<< orphan*/  type; int /*<<< orphan*/  len; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NFTA_IMMEDIATE_DATA ; 
 size_t NFTA_IMMEDIATE_DREG ; 
 int nft_data_init (struct nft_ctx const*,int /*<<< orphan*/ *,int,struct nft_data_desc*,struct nlattr const* const) ; 
 int /*<<< orphan*/  nft_data_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nft_immediate_expr* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_parse_register (struct nlattr const* const) ; 
 int nft_validate_register_store (struct nft_ctx const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_immediate_init(const struct nft_ctx *ctx,
			      const struct nft_expr *expr,
			      const struct nlattr * const tb[])
{
	struct nft_immediate_expr *priv = nft_expr_priv(expr);
	struct nft_data_desc desc;
	int err;

	if (tb[NFTA_IMMEDIATE_DREG] == NULL ||
	    tb[NFTA_IMMEDIATE_DATA] == NULL)
		return -EINVAL;

	err = nft_data_init(ctx, &priv->data, sizeof(priv->data), &desc,
			    tb[NFTA_IMMEDIATE_DATA]);
	if (err < 0)
		return err;

	priv->dlen = desc.len;

	priv->dreg = nft_parse_register(tb[NFTA_IMMEDIATE_DREG]);
	err = nft_validate_register_store(ctx, priv->dreg, &priv->data,
					  desc.type, desc.len);
	if (err < 0)
		goto err1;

	return 0;

err1:
	nft_data_release(&priv->data, desc.type);
	return err;
}