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

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSD_FILE_SHUTDOWN ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dispose ; 
 int /*<<< orphan*/  fsnotify_put_group (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsnotify_wait_marks_destroyed () ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lease_unregister_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lru_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_file_cache_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nfsd_file_fsnotify_group ; 
 int /*<<< orphan*/ * nfsd_file_hashtbl ; 
 int /*<<< orphan*/  nfsd_file_lease_notifier ; 
 int /*<<< orphan*/  nfsd_file_lru ; 
 int /*<<< orphan*/  nfsd_file_lru_flags ; 
 int /*<<< orphan*/ * nfsd_file_mark_slab ; 
 int /*<<< orphan*/  nfsd_file_shrinker ; 
 int /*<<< orphan*/ * nfsd_file_slab ; 
 int /*<<< orphan*/  nfsd_filecache_laundrette ; 
 int /*<<< orphan*/  rcu_barrier () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_shrinker (int /*<<< orphan*/ *) ; 

void
nfsd_file_cache_shutdown(void)
{
	LIST_HEAD(dispose);

	set_bit(NFSD_FILE_SHUTDOWN, &nfsd_file_lru_flags);

	lease_unregister_notifier(&nfsd_file_lease_notifier);
	unregister_shrinker(&nfsd_file_shrinker);
	/*
	 * make sure all callers of nfsd_file_lru_cb are done before
	 * calling nfsd_file_cache_purge
	 */
	cancel_delayed_work_sync(&nfsd_filecache_laundrette);
	nfsd_file_cache_purge(NULL);
	list_lru_destroy(&nfsd_file_lru);
	rcu_barrier();
	fsnotify_put_group(nfsd_file_fsnotify_group);
	nfsd_file_fsnotify_group = NULL;
	kmem_cache_destroy(nfsd_file_slab);
	nfsd_file_slab = NULL;
	fsnotify_wait_marks_destroyed();
	kmem_cache_destroy(nfsd_file_mark_slab);
	nfsd_file_mark_slab = NULL;
	kfree(nfsd_file_hashtbl);
	nfsd_file_hashtbl = NULL;
}