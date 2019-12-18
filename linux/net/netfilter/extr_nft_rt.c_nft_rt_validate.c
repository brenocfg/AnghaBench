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
struct nft_rt {int key; } ;
struct nft_expr {int dummy; } ;
struct nft_data {int dummy; } ;
struct nft_ctx {int /*<<< orphan*/  chain; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NFT_RT_CLASSID 132 
#define  NFT_RT_NEXTHOP4 131 
#define  NFT_RT_NEXTHOP6 130 
#define  NFT_RT_TCPMSS 129 
#define  NFT_RT_XFRM 128 
 int NF_INET_FORWARD ; 
 int NF_INET_LOCAL_OUT ; 
 int NF_INET_POST_ROUTING ; 
 int nft_chain_validate_hooks (int /*<<< orphan*/ ,unsigned int) ; 
 struct nft_rt* nft_expr_priv (struct nft_expr const*) ; 

__attribute__((used)) static int nft_rt_validate(const struct nft_ctx *ctx, const struct nft_expr *expr,
			   const struct nft_data **data)
{
	const struct nft_rt *priv = nft_expr_priv(expr);
	unsigned int hooks;

	switch (priv->key) {
	case NFT_RT_NEXTHOP4:
	case NFT_RT_NEXTHOP6:
	case NFT_RT_CLASSID:
	case NFT_RT_XFRM:
		return 0;
	case NFT_RT_TCPMSS:
		hooks = (1 << NF_INET_FORWARD) |
			(1 << NF_INET_LOCAL_OUT) |
			(1 << NF_INET_POST_ROUTING);
		break;
	default:
		return -EINVAL;
	}

	return nft_chain_validate_hooks(ctx->chain, hooks);
}