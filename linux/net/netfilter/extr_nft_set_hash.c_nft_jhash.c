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
struct nft_set {int klen; } ;
struct nft_hash {int /*<<< orphan*/  buckets; int /*<<< orphan*/  seed; } ;
struct nft_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jhash (struct nft_data const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jhash_1word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_data* nft_set_ext_key (struct nft_set_ext const*) ; 
 int /*<<< orphan*/  reciprocal_scale (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 nft_jhash(const struct nft_set *set, const struct nft_hash *priv,
		     const struct nft_set_ext *ext)
{
	const struct nft_data *key = nft_set_ext_key(ext);
	u32 hash, k1;

	if (set->klen == 4) {
		k1 = *(u32 *)key;
		hash = jhash_1word(k1, priv->seed);
	} else {
		hash = jhash(key, set->klen, priv->seed);
	}
	hash = reciprocal_scale(hash, priv->buckets);

	return hash;
}