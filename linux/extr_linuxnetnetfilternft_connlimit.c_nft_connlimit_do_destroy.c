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
struct nft_ctx {int /*<<< orphan*/  family; int /*<<< orphan*/  net; } ;
struct nft_connlimit {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  nf_conncount_cache_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_netns_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nft_connlimit_do_destroy(const struct nft_ctx *ctx,
				     struct nft_connlimit *priv)
{
	nf_ct_netns_put(ctx->net, ctx->family);
	nf_conncount_cache_free(&priv->list);
}