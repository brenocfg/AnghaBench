#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fscache_cache {TYPE_2__* tag; int /*<<< orphan*/  kobj; int /*<<< orphan*/  object_list; int /*<<< orphan*/  object_count; TYPE_1__* ops; int /*<<< orphan*/  link; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/ * cache; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* dissociate_pages ) (struct fscache_cache*) ;int /*<<< orphan*/  (* sync_cache ) (struct fscache_cache*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  FSCACHE_CACHE_WITHDRAWN ; 
 int /*<<< orphan*/  FSCACHE_TAG_RESERVED ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dying_objects ; 
 int /*<<< orphan*/  fscache_addremove_sem ; 
 int /*<<< orphan*/  fscache_cache_cleared_wq ; 
 int /*<<< orphan*/  fscache_n_cop_dissociate_pages ; 
 int /*<<< orphan*/  fscache_n_cop_sync_cache ; 
 int /*<<< orphan*/  fscache_release_cache_tag (TYPE_2__*) ; 
 int /*<<< orphan*/  fscache_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_stat_d (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_withdraw_all_objects (struct fscache_cache*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fscache_cache*) ; 
 int /*<<< orphan*/  stub2 (struct fscache_cache*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void fscache_withdraw_cache(struct fscache_cache *cache)
{
	LIST_HEAD(dying_objects);

	_enter("");

	pr_notice("Withdrawing cache \"%s\"\n",
		  cache->tag->name);

	/* make the cache unavailable for cookie acquisition */
	if (test_and_set_bit(FSCACHE_CACHE_WITHDRAWN, &cache->flags))
		BUG();

	down_write(&fscache_addremove_sem);
	list_del_init(&cache->link);
	cache->tag->cache = NULL;
	up_write(&fscache_addremove_sem);

	/* make sure all pages pinned by operations on behalf of the netfs are
	 * written to disk */
	fscache_stat(&fscache_n_cop_sync_cache);
	cache->ops->sync_cache(cache);
	fscache_stat_d(&fscache_n_cop_sync_cache);

	/* dissociate all the netfs pages backed by this cache from the block
	 * mappings in the cache */
	fscache_stat(&fscache_n_cop_dissociate_pages);
	cache->ops->dissociate_pages(cache);
	fscache_stat_d(&fscache_n_cop_dissociate_pages);

	/* we now have to destroy all the active objects pertaining to this
	 * cache - which we do by passing them off to thread pool to be
	 * disposed of */
	_debug("destroy");

	fscache_withdraw_all_objects(cache, &dying_objects);

	/* wait for all extant objects to finish their outstanding operations
	 * and go away */
	_debug("wait for finish");
	wait_event(fscache_cache_cleared_wq,
		   atomic_read(&cache->object_count) == 0);
	_debug("wait for clearance");
	wait_event(fscache_cache_cleared_wq,
		   list_empty(&cache->object_list));
	_debug("cleared");
	ASSERT(list_empty(&dying_objects));

	kobject_put(cache->kobj);

	clear_bit(FSCACHE_TAG_RESERVED, &cache->tag->flags);
	fscache_release_cache_tag(cache->tag);
	cache->tag = NULL;

	_leave("");
}