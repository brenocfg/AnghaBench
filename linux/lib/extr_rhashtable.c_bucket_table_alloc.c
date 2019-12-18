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
struct rhashtable {int dummy; } ;
struct lock_class_key {int dummy; } ;
struct bucket_table {size_t size; int /*<<< orphan*/ * buckets; int /*<<< orphan*/  hash_rnd; int /*<<< orphan*/  walkers; int /*<<< orphan*/  rcu; int /*<<< orphan*/  dep_map; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RHT_NULLS_HEAD (int /*<<< orphan*/ ) ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  buckets ; 
 int /*<<< orphan*/  get_random_u32 () ; 
 struct bucket_table* kvzalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lockdep_init_map (int /*<<< orphan*/ *,char*,struct lock_class_key*,int /*<<< orphan*/ ) ; 
 struct bucket_table* nested_bucket_table_alloc (struct rhashtable*,size_t,int) ; 
 int /*<<< orphan*/  rcu_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  struct_size (struct bucket_table*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static struct bucket_table *bucket_table_alloc(struct rhashtable *ht,
					       size_t nbuckets,
					       gfp_t gfp)
{
	struct bucket_table *tbl = NULL;
	size_t size;
	int i;
	static struct lock_class_key __key;

	tbl = kvzalloc(struct_size(tbl, buckets, nbuckets), gfp);

	size = nbuckets;

	if (tbl == NULL && (gfp & ~__GFP_NOFAIL) != GFP_KERNEL) {
		tbl = nested_bucket_table_alloc(ht, nbuckets, gfp);
		nbuckets = 0;
	}

	if (tbl == NULL)
		return NULL;

	lockdep_init_map(&tbl->dep_map, "rhashtable_bucket", &__key, 0);

	tbl->size = size;

	rcu_head_init(&tbl->rcu);
	INIT_LIST_HEAD(&tbl->walkers);

	tbl->hash_rnd = get_random_u32();

	for (i = 0; i < nbuckets; i++)
		INIT_RHT_NULLS_HEAD(tbl->buckets[i]);

	return tbl;
}