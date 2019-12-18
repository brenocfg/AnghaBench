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
struct nft_nat {int type; } ;
struct nft_expr {int dummy; } ;
struct nft_data {int dummy; } ;
struct nft_ctx {int /*<<< orphan*/  chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFT_CHAIN_T_NAT ; 
#define  NFT_NAT_DNAT 129 
#define  NFT_NAT_SNAT 128 
 int NF_INET_LOCAL_IN ; 
 int NF_INET_LOCAL_OUT ; 
 int NF_INET_POST_ROUTING ; 
 int NF_INET_PRE_ROUTING ; 
 int nft_chain_validate_dependency (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nft_chain_validate_hooks (int /*<<< orphan*/ ,int) ; 
 struct nft_nat* nft_expr_priv (struct nft_expr const*) ; 

__attribute__((used)) static int nft_nat_validate(const struct nft_ctx *ctx,
			    const struct nft_expr *expr,
			    const struct nft_data **data)
{
	struct nft_nat *priv = nft_expr_priv(expr);
	int err;

	err = nft_chain_validate_dependency(ctx->chain, NFT_CHAIN_T_NAT);
	if (err < 0)
		return err;

	switch (priv->type) {
	case NFT_NAT_SNAT:
		err = nft_chain_validate_hooks(ctx->chain,
					       (1 << NF_INET_POST_ROUTING) |
					       (1 << NF_INET_LOCAL_IN));
		break;
	case NFT_NAT_DNAT:
		err = nft_chain_validate_hooks(ctx->chain,
					       (1 << NF_INET_PRE_ROUTING) |
					       (1 << NF_INET_LOCAL_OUT));
		break;
	}

	return err;
}