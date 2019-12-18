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
struct nft_set {int dummy; } ;
struct nft_rhash {int /*<<< orphan*/  ht; int /*<<< orphan*/  gc_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nft_rhash_elem_destroy ; 
 struct nft_rhash* nft_set_priv (struct nft_set const*) ; 
 int /*<<< orphan*/  rcu_barrier () ; 
 int /*<<< orphan*/  rhashtable_free_and_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void nft_rhash_destroy(const struct nft_set *set)
{
	struct nft_rhash *priv = nft_set_priv(set);

	cancel_delayed_work_sync(&priv->gc_work);
	rcu_barrier();
	rhashtable_free_and_destroy(&priv->ht, nft_rhash_elem_destroy,
				    (void *)set);
}