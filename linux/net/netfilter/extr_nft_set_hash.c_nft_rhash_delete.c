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
struct nft_set {int dummy; } ;
struct nft_rhash_elem {int /*<<< orphan*/  node; } ;
struct nft_rhash_cmp_arg {int /*<<< orphan*/  const* key; struct nft_set const* set; int /*<<< orphan*/  genmask; } ;
struct nft_rhash {int /*<<< orphan*/  ht; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFT_GENMASK_ANY ; 
 int /*<<< orphan*/  nft_rhash_params ; 
 struct nft_rhash* nft_set_priv (struct nft_set const*) ; 
 struct nft_rhash_elem* rhashtable_lookup (int /*<<< orphan*/ *,struct nft_rhash_cmp_arg*,int /*<<< orphan*/ ) ; 
 scalar_t__ rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nft_rhash_delete(const struct nft_set *set,
			     const u32 *key)
{
	struct nft_rhash *priv = nft_set_priv(set);
	struct nft_rhash_cmp_arg arg = {
		.genmask = NFT_GENMASK_ANY,
		.set = set,
		.key = key,
	};
	struct nft_rhash_elem *he;

	he = rhashtable_lookup(&priv->ht, &arg, nft_rhash_params);
	if (he == NULL)
		return false;

	return rhashtable_remove_fast(&priv->ht, &he->node, nft_rhash_params) == 0;
}