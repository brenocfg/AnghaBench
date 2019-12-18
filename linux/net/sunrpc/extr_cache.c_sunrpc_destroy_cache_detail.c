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
struct cache_detail {int /*<<< orphan*/  hash_lock; int /*<<< orphan*/  others; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_cleaner ; 
 int /*<<< orphan*/  cache_list ; 
 int /*<<< orphan*/  cache_list_lock ; 
 int /*<<< orphan*/  cache_purge (struct cache_detail*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct cache_detail* current_detail ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void sunrpc_destroy_cache_detail(struct cache_detail *cd)
{
	cache_purge(cd);
	spin_lock(&cache_list_lock);
	spin_lock(&cd->hash_lock);
	if (current_detail == cd)
		current_detail = NULL;
	list_del_init(&cd->others);
	spin_unlock(&cd->hash_lock);
	spin_unlock(&cache_list_lock);
	if (list_empty(&cache_list)) {
		/* module must be being unloaded so its safe to kill the worker */
		cancel_delayed_work_sync(&cache_cleaner);
	}
}