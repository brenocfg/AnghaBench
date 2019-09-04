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
struct nft_rule {int dummy; } ;
struct nft_ctx {TYPE_1__* chain; int /*<<< orphan*/  net; } ;
struct TYPE_2__ {int /*<<< orphan*/  use; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  nft_deactivate_next (int /*<<< orphan*/ ,struct nft_rule*) ; 
 scalar_t__ nft_is_active_next (int /*<<< orphan*/ ,struct nft_rule*) ; 

__attribute__((used)) static int
nf_tables_delrule_deactivate(struct nft_ctx *ctx, struct nft_rule *rule)
{
	/* You cannot delete the same rule twice */
	if (nft_is_active_next(ctx->net, rule)) {
		nft_deactivate_next(ctx->net, rule);
		ctx->chain->use--;
		return 0;
	}
	return -ENOENT;
}