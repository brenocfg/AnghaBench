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
struct rhashtable_params {int /*<<< orphan*/  key_len; int /*<<< orphan*/  nelem_hint; } ;
struct nlattr {int dummy; } ;
struct nft_set_desc {scalar_t__ size; } ;
struct nft_set {int flags; int /*<<< orphan*/  klen; } ;
struct nft_rhash {int /*<<< orphan*/  gc_work; int /*<<< orphan*/  ht; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DEFERRABLE_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFT_RHASH_ELEMENT_HINT ; 
 int NFT_SET_TIMEOUT ; 
 int /*<<< orphan*/  nft_rhash_gc ; 
 int /*<<< orphan*/  nft_rhash_gc_init (struct nft_set const*) ; 
 struct rhashtable_params nft_rhash_params ; 
 struct nft_rhash* nft_set_priv (struct nft_set const*) ; 
 int rhashtable_init (int /*<<< orphan*/ *,struct rhashtable_params*) ; 

__attribute__((used)) static int nft_rhash_init(const struct nft_set *set,
			  const struct nft_set_desc *desc,
			  const struct nlattr * const tb[])
{
	struct nft_rhash *priv = nft_set_priv(set);
	struct rhashtable_params params = nft_rhash_params;
	int err;

	params.nelem_hint = desc->size ?: NFT_RHASH_ELEMENT_HINT;
	params.key_len	  = set->klen;

	err = rhashtable_init(&priv->ht, &params);
	if (err < 0)
		return err;

	INIT_DEFERRABLE_WORK(&priv->gc_work, nft_rhash_gc);
	if (set->flags & NFT_SET_TIMEOUT)
		nft_rhash_gc_init(set);

	return 0;
}