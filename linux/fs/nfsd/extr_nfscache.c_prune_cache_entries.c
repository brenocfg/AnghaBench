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
struct nfsd_net {unsigned int drc_hashsize; struct nfsd_drc_bucket* drc_hashtbl; } ;
struct nfsd_drc_bucket {int /*<<< orphan*/  cache_lock; int /*<<< orphan*/  lru_head; } ;

/* Variables and functions */
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ prune_bucket (struct nfsd_drc_bucket*,struct nfsd_net*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long
prune_cache_entries(struct nfsd_net *nn)
{
	unsigned int i;
	long freed = 0;

	for (i = 0; i < nn->drc_hashsize; i++) {
		struct nfsd_drc_bucket *b = &nn->drc_hashtbl[i];

		if (list_empty(&b->lru_head))
			continue;
		spin_lock(&b->cache_lock);
		freed += prune_bucket(b, nn);
		spin_unlock(&b->cache_lock);
	}
	return freed;
}