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
struct nft_set_ext {int dummy; } ;
struct nft_set {int dummy; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFT_SET_EXT_EXPR ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  nf_tables_expr_destroy (struct nft_ctx const*,int /*<<< orphan*/ ) ; 
 struct nft_set_ext* nft_set_elem_ext (struct nft_set const*,void*) ; 
 scalar_t__ nft_set_ext_exists (struct nft_set_ext*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nft_set_ext_expr (struct nft_set_ext*) ; 

__attribute__((used)) static void nf_tables_set_elem_destroy(const struct nft_ctx *ctx,
				       const struct nft_set *set, void *elem)
{
	struct nft_set_ext *ext = nft_set_elem_ext(set, elem);

	if (nft_set_ext_exists(ext, NFT_SET_EXT_EXPR))
		nf_tables_expr_destroy(ctx, nft_set_ext_expr(ext));
	kfree(elem);
}