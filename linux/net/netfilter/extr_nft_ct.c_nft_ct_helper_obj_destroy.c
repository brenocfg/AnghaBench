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
struct nft_object {int dummy; } ;
struct nft_ctx {int /*<<< orphan*/  family; int /*<<< orphan*/  net; } ;
struct nft_ct_helper_obj {scalar_t__ helper6; scalar_t__ helper4; } ;

/* Variables and functions */
 int /*<<< orphan*/  nf_conntrack_helper_put (scalar_t__) ; 
 int /*<<< orphan*/  nf_ct_netns_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_ct_helper_obj* nft_obj_data (struct nft_object*) ; 

__attribute__((used)) static void nft_ct_helper_obj_destroy(const struct nft_ctx *ctx,
				      struct nft_object *obj)
{
	struct nft_ct_helper_obj *priv = nft_obj_data(obj);

	if (priv->helper4)
		nf_conntrack_helper_put(priv->helper4);
	if (priv->helper6)
		nf_conntrack_helper_put(priv->helper6);

	nf_ct_netns_put(ctx->net, ctx->family);
}