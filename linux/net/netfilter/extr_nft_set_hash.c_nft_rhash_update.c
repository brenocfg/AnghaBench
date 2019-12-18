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
typedef  int /*<<< orphan*/  u32 ;
struct nft_set_ext {int dummy; } ;
struct nft_set {int dummy; } ;
struct nft_rhash_elem {struct nft_set_ext ext; int /*<<< orphan*/  node; } ;
struct nft_rhash_cmp_arg {int /*<<< orphan*/  const* key; struct nft_set* set; int /*<<< orphan*/  genmask; } ;
struct nft_rhash {int /*<<< orphan*/  ht; } ;
struct nft_regs {int dummy; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nft_rhash_elem*) ; 
 int /*<<< orphan*/  NFT_GENMASK_ANY ; 
 int /*<<< orphan*/  nft_rhash_params ; 
 int /*<<< orphan*/  nft_set_elem_destroy (struct nft_set*,struct nft_rhash_elem*,int) ; 
 struct nft_rhash* nft_set_priv (struct nft_set*) ; 
 struct nft_rhash_elem* rhashtable_lookup (int /*<<< orphan*/ *,struct nft_rhash_cmp_arg*,int /*<<< orphan*/ ) ; 
 struct nft_rhash_elem* rhashtable_lookup_get_insert_key (int /*<<< orphan*/ *,struct nft_rhash_cmp_arg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nft_rhash_update(struct nft_set *set, const u32 *key,
			     void *(*new)(struct nft_set *,
					  const struct nft_expr *,
					  struct nft_regs *regs),
			     const struct nft_expr *expr,
			     struct nft_regs *regs,
			     const struct nft_set_ext **ext)
{
	struct nft_rhash *priv = nft_set_priv(set);
	struct nft_rhash_elem *he, *prev;
	struct nft_rhash_cmp_arg arg = {
		.genmask = NFT_GENMASK_ANY,
		.set	 = set,
		.key	 = key,
	};

	he = rhashtable_lookup(&priv->ht, &arg, nft_rhash_params);
	if (he != NULL)
		goto out;

	he = new(set, expr, regs);
	if (he == NULL)
		goto err1;

	prev = rhashtable_lookup_get_insert_key(&priv->ht, &arg, &he->node,
						nft_rhash_params);
	if (IS_ERR(prev))
		goto err2;

	/* Another cpu may race to insert the element with the same key */
	if (prev) {
		nft_set_elem_destroy(set, he, true);
		he = prev;
	}

out:
	*ext = &he->ext;
	return true;

err2:
	nft_set_elem_destroy(set, he, true);
err1:
	return false;
}