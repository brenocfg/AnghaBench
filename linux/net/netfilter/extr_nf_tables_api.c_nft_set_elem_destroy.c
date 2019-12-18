#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nft_set_ext {int dummy; } ;
struct nft_set {int /*<<< orphan*/  dtype; TYPE_1__* table; int /*<<< orphan*/  net; } ;
struct nft_expr {TYPE_3__* ops; } ;
struct nft_ctx {int /*<<< orphan*/  family; int /*<<< orphan*/  net; } ;
struct TYPE_8__ {int /*<<< orphan*/  use; } ;
struct TYPE_7__ {TYPE_2__* type; int /*<<< orphan*/  (* destroy_clone ) (struct nft_ctx*,struct nft_expr*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  owner; } ;
struct TYPE_5__ {int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFT_DATA_VALUE ; 
 int /*<<< orphan*/  NFT_SET_EXT_DATA ; 
 int /*<<< orphan*/  NFT_SET_EXT_EXPR ; 
 int /*<<< orphan*/  NFT_SET_EXT_OBJREF ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_tables_expr_destroy (struct nft_ctx*,struct nft_expr*) ; 
 int /*<<< orphan*/  nft_data_release (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_set_ext* nft_set_elem_ext (struct nft_set const*,void*) ; 
 int /*<<< orphan*/  nft_set_ext_data (struct nft_set_ext*) ; 
 scalar_t__ nft_set_ext_exists (struct nft_set_ext*,int /*<<< orphan*/ ) ; 
 struct nft_expr* nft_set_ext_expr (struct nft_set_ext*) ; 
 int /*<<< orphan*/  nft_set_ext_key (struct nft_set_ext*) ; 
 TYPE_4__** nft_set_ext_obj (struct nft_set_ext*) ; 
 int /*<<< orphan*/  read_pnet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nft_ctx*,struct nft_expr*) ; 

void nft_set_elem_destroy(const struct nft_set *set, void *elem,
			  bool destroy_expr)
{
	struct nft_set_ext *ext = nft_set_elem_ext(set, elem);
	struct nft_ctx ctx = {
		.net	= read_pnet(&set->net),
		.family	= set->table->family,
	};

	nft_data_release(nft_set_ext_key(ext), NFT_DATA_VALUE);
	if (nft_set_ext_exists(ext, NFT_SET_EXT_DATA))
		nft_data_release(nft_set_ext_data(ext), set->dtype);
	if (destroy_expr && nft_set_ext_exists(ext, NFT_SET_EXT_EXPR)) {
		struct nft_expr *expr = nft_set_ext_expr(ext);

		if (expr->ops->destroy_clone) {
			expr->ops->destroy_clone(&ctx, expr);
			module_put(expr->ops->type->owner);
		} else {
			nf_tables_expr_destroy(&ctx, expr);
		}
	}
	if (nft_set_ext_exists(ext, NFT_SET_EXT_OBJREF))
		(*nft_set_ext_obj(ext))->use--;
	kfree(elem);
}