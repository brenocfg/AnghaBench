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
struct nlattr {int dummy; } ;
struct nft_set_desc {int /*<<< orphan*/  size; } ;
struct nft_set {int dummy; } ;
struct nft_hash {int /*<<< orphan*/  seed; int /*<<< orphan*/  buckets; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nft_hash_buckets (int /*<<< orphan*/ ) ; 
 struct nft_hash* nft_set_priv (struct nft_set const*) ; 

__attribute__((used)) static int nft_hash_init(const struct nft_set *set,
			 const struct nft_set_desc *desc,
			 const struct nlattr * const tb[])
{
	struct nft_hash *priv = nft_set_priv(set);

	priv->buckets = nft_hash_buckets(desc->size);
	get_random_bytes(&priv->seed, sizeof(priv->seed));

	return 0;
}