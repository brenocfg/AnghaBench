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
struct nft_expr {int dummy; } ;
struct nft_data {int dummy; } ;
struct nft_ctx {int /*<<< orphan*/  chain; } ;

/* Variables and functions */
 int NF_BR_LOCAL_IN ; 
 int NF_BR_PRE_ROUTING ; 
 int nft_chain_validate_hooks (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nft_reject_bridge_validate(const struct nft_ctx *ctx,
				      const struct nft_expr *expr,
				      const struct nft_data **data)
{
	return nft_chain_validate_hooks(ctx->chain, (1 << NF_BR_PRE_ROUTING) |
						    (1 << NF_BR_LOCAL_IN));
}