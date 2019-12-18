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
struct nft_rule {int dummy; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFT_TRANS_RELEASE ; 
 int /*<<< orphan*/  nf_tables_rule_destroy (struct nft_ctx const*,struct nft_rule*) ; 
 int /*<<< orphan*/  nft_rule_expr_deactivate (struct nft_ctx const*,struct nft_rule*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nf_tables_rule_release(const struct nft_ctx *ctx,
				   struct nft_rule *rule)
{
	nft_rule_expr_deactivate(ctx, rule, NFT_TRANS_RELEASE);
	nf_tables_rule_destroy(ctx, rule);
}