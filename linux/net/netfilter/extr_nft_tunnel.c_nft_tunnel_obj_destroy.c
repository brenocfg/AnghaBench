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
struct nft_tunnel_obj {int /*<<< orphan*/  md; } ;
struct nft_object {int dummy; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  metadata_dst_free (int /*<<< orphan*/ ) ; 
 struct nft_tunnel_obj* nft_obj_data (struct nft_object*) ; 

__attribute__((used)) static void nft_tunnel_obj_destroy(const struct nft_ctx *ctx,
				   struct nft_object *obj)
{
	struct nft_tunnel_obj *priv = nft_obj_data(obj);

	metadata_dst_free(priv->md);
}