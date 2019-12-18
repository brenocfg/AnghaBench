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
struct nft_expr {int dummy; } ;
struct nft_data_desc {int /*<<< orphan*/  len; } ;
struct nft_ctx {int dummy; } ;
struct nft_cmp_expr {int /*<<< orphan*/  len; int /*<<< orphan*/  op; int /*<<< orphan*/  sreg; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 size_t NFTA_CMP_DATA ; 
 size_t NFTA_CMP_OP ; 
 size_t NFTA_CMP_SREG ; 
 int nft_data_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct nft_data_desc*,struct nlattr const* const) ; 
 struct nft_cmp_expr* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_parse_register (struct nlattr const* const) ; 
 int nft_validate_register_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_cmp_init(const struct nft_ctx *ctx, const struct nft_expr *expr,
			const struct nlattr * const tb[])
{
	struct nft_cmp_expr *priv = nft_expr_priv(expr);
	struct nft_data_desc desc;
	int err;

	err = nft_data_init(NULL, &priv->data, sizeof(priv->data), &desc,
			    tb[NFTA_CMP_DATA]);
	if (err < 0)
		return err;

	priv->sreg = nft_parse_register(tb[NFTA_CMP_SREG]);
	err = nft_validate_register_load(priv->sreg, desc.len);
	if (err < 0)
		return err;

	priv->op  = ntohl(nla_get_be32(tb[NFTA_CMP_OP]));
	priv->len = desc.len;
	return 0;
}