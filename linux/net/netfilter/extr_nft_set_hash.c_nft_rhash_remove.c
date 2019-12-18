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
struct nft_set_elem {struct nft_rhash_elem* priv; } ;
struct nft_set {int dummy; } ;
struct nft_rhash_elem {int /*<<< orphan*/  node; } ;
struct nft_rhash {int /*<<< orphan*/  ht; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nft_rhash_params ; 
 struct nft_rhash* nft_set_priv (struct nft_set const*) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nft_rhash_remove(const struct net *net,
			     const struct nft_set *set,
			     const struct nft_set_elem *elem)
{
	struct nft_rhash *priv = nft_set_priv(set);
	struct nft_rhash_elem *he = elem->priv;

	rhashtable_remove_fast(&priv->ht, &he->node, nft_rhash_params);
}