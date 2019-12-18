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
struct kmem_cache {int limit; int shared; int batchcount; int size; int /*<<< orphan*/  name; int /*<<< orphan*/  num; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int cache_random_seq_create (struct kmem_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int do_tune_cpucache (struct kmem_cache*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_root_cache (struct kmem_cache*) ; 
 struct kmem_cache* memcg_root_cache (struct kmem_cache*) ; 
 int num_possible_cpus () ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int enable_cpucache(struct kmem_cache *cachep, gfp_t gfp)
{
	int err;
	int limit = 0;
	int shared = 0;
	int batchcount = 0;

	err = cache_random_seq_create(cachep, cachep->num, gfp);
	if (err)
		goto end;

	if (!is_root_cache(cachep)) {
		struct kmem_cache *root = memcg_root_cache(cachep);
		limit = root->limit;
		shared = root->shared;
		batchcount = root->batchcount;
	}

	if (limit && shared && batchcount)
		goto skip_setup;
	/*
	 * The head array serves three purposes:
	 * - create a LIFO ordering, i.e. return objects that are cache-warm
	 * - reduce the number of spinlock operations.
	 * - reduce the number of linked list operations on the slab and
	 *   bufctl chains: array operations are cheaper.
	 * The numbers are guessed, we should auto-tune as described by
	 * Bonwick.
	 */
	if (cachep->size > 131072)
		limit = 1;
	else if (cachep->size > PAGE_SIZE)
		limit = 8;
	else if (cachep->size > 1024)
		limit = 24;
	else if (cachep->size > 256)
		limit = 54;
	else
		limit = 120;

	/*
	 * CPU bound tasks (e.g. network routing) can exhibit cpu bound
	 * allocation behaviour: Most allocs on one cpu, most free operations
	 * on another cpu. For these cases, an efficient object passing between
	 * cpus is necessary. This is provided by a shared array. The array
	 * replaces Bonwick's magazine layer.
	 * On uniprocessor, it's functionally equivalent (but less efficient)
	 * to a larger limit. Thus disabled by default.
	 */
	shared = 0;
	if (cachep->size <= PAGE_SIZE && num_possible_cpus() > 1)
		shared = 8;

#if DEBUG
	/*
	 * With debugging enabled, large batchcount lead to excessively long
	 * periods with disabled local interrupts. Limit the batchcount
	 */
	if (limit > 32)
		limit = 32;
#endif
	batchcount = (limit + 1) / 2;
skip_setup:
	err = do_tune_cpucache(cachep, limit, batchcount, shared, gfp);
end:
	if (err)
		pr_err("enable_cpucache failed for %s, error %d\n",
		       cachep->name, -err);
	return err;
}