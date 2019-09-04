#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  seeks; int /*<<< orphan*/  scan_objects; int /*<<< orphan*/  count_objects; } ;
struct mb_cache {int c_bucket_bits; unsigned long c_max_entries; int /*<<< orphan*/  c_shrink_work; struct mb_cache* c_hash; TYPE_1__ c_shrink; int /*<<< orphan*/  c_list_lock; int /*<<< orphan*/  c_list; } ;
struct hlist_bl_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_SEEKS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_BL_HEAD (struct mb_cache*) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mb_cache*) ; 
 struct mb_cache* kmalloc_array (unsigned long,int,int /*<<< orphan*/ ) ; 
 struct mb_cache* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_cache_count ; 
 int /*<<< orphan*/  mb_cache_scan ; 
 int /*<<< orphan*/  mb_cache_shrink_worker ; 
 scalar_t__ register_shrinker (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct mb_cache *mb_cache_create(int bucket_bits)
{
	struct mb_cache *cache;
	unsigned long bucket_count = 1UL << bucket_bits;
	unsigned long i;

	cache = kzalloc(sizeof(struct mb_cache), GFP_KERNEL);
	if (!cache)
		goto err_out;
	cache->c_bucket_bits = bucket_bits;
	cache->c_max_entries = bucket_count << 4;
	INIT_LIST_HEAD(&cache->c_list);
	spin_lock_init(&cache->c_list_lock);
	cache->c_hash = kmalloc_array(bucket_count,
				      sizeof(struct hlist_bl_head),
				      GFP_KERNEL);
	if (!cache->c_hash) {
		kfree(cache);
		goto err_out;
	}
	for (i = 0; i < bucket_count; i++)
		INIT_HLIST_BL_HEAD(&cache->c_hash[i]);

	cache->c_shrink.count_objects = mb_cache_count;
	cache->c_shrink.scan_objects = mb_cache_scan;
	cache->c_shrink.seeks = DEFAULT_SEEKS;
	if (register_shrinker(&cache->c_shrink)) {
		kfree(cache->c_hash);
		kfree(cache);
		goto err_out;
	}

	INIT_WORK(&cache->c_shrink_work, mb_cache_shrink_worker);

	return cache;

err_out:
	return NULL;
}