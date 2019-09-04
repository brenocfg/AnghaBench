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
struct nft_set_binding {int /*<<< orphan*/  list; } ;
struct nft_set {int /*<<< orphan*/  bindings; } ;
struct nft_ctx {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_tables_set_destroy (struct nft_ctx const*,struct nft_set*) ; 
 scalar_t__ nft_is_active (int /*<<< orphan*/ ,struct nft_set*) ; 
 scalar_t__ nft_set_is_anonymous (struct nft_set*) ; 

void nf_tables_unbind_set(const struct nft_ctx *ctx, struct nft_set *set,
			  struct nft_set_binding *binding)
{
	list_del_rcu(&binding->list);

	if (list_empty(&set->bindings) && nft_set_is_anonymous(set) &&
	    nft_is_active(ctx->net, set))
		nf_tables_set_destroy(ctx, set);
}