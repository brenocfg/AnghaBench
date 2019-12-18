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
struct rhashtable_iter {int dummy; } ;
struct nft_set_iter {scalar_t__ count; scalar_t__ skip; int /*<<< orphan*/  err; int /*<<< orphan*/  (* fn ) (struct nft_ctx const*,struct nft_set*,struct nft_set_iter*,struct nft_set_elem*) ;int /*<<< orphan*/  genmask; } ;
struct nft_set_elem {struct nft_rhash_elem* priv; } ;
struct nft_set {int dummy; } ;
struct nft_rhash_elem {int /*<<< orphan*/  ext; } ;
struct nft_rhash {int /*<<< orphan*/  ht; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 scalar_t__ IS_ERR (struct nft_rhash_elem*) ; 
 int /*<<< orphan*/  PTR_ERR (struct nft_rhash_elem*) ; 
 int /*<<< orphan*/  nft_set_elem_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nft_set_elem_expired (int /*<<< orphan*/ *) ; 
 struct nft_rhash* nft_set_priv (struct nft_set*) ; 
 int /*<<< orphan*/  rhashtable_walk_enter (int /*<<< orphan*/ *,struct rhashtable_iter*) ; 
 int /*<<< orphan*/  rhashtable_walk_exit (struct rhashtable_iter*) ; 
 struct nft_rhash_elem* rhashtable_walk_next (struct rhashtable_iter*) ; 
 int /*<<< orphan*/  rhashtable_walk_start (struct rhashtable_iter*) ; 
 int /*<<< orphan*/  rhashtable_walk_stop (struct rhashtable_iter*) ; 
 int /*<<< orphan*/  stub1 (struct nft_ctx const*,struct nft_set*,struct nft_set_iter*,struct nft_set_elem*) ; 

__attribute__((used)) static void nft_rhash_walk(const struct nft_ctx *ctx, struct nft_set *set,
			   struct nft_set_iter *iter)
{
	struct nft_rhash *priv = nft_set_priv(set);
	struct nft_rhash_elem *he;
	struct rhashtable_iter hti;
	struct nft_set_elem elem;

	rhashtable_walk_enter(&priv->ht, &hti);
	rhashtable_walk_start(&hti);

	while ((he = rhashtable_walk_next(&hti))) {
		if (IS_ERR(he)) {
			if (PTR_ERR(he) != -EAGAIN) {
				iter->err = PTR_ERR(he);
				break;
			}

			continue;
		}

		if (iter->count < iter->skip)
			goto cont;
		if (nft_set_elem_expired(&he->ext))
			goto cont;
		if (!nft_set_elem_active(&he->ext, iter->genmask))
			goto cont;

		elem.priv = he;

		iter->err = iter->fn(ctx, set, iter, &elem);
		if (iter->err < 0)
			break;

cont:
		iter->count++;
	}
	rhashtable_walk_stop(&hti);
	rhashtable_walk_exit(&hti);
}