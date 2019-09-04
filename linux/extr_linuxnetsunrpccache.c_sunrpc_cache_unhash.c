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
struct cache_head {int /*<<< orphan*/  cache_list; } ;
struct cache_detail {int /*<<< orphan*/  hash_lock; int /*<<< orphan*/  entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_put (struct cache_head*,struct cache_detail*) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void sunrpc_cache_unhash(struct cache_detail *cd, struct cache_head *h)
{
	write_lock(&cd->hash_lock);
	if (!hlist_unhashed(&h->cache_list)){
		hlist_del_init(&h->cache_list);
		cd->entries--;
		write_unlock(&cd->hash_lock);
		cache_put(h, cd);
	} else
		write_unlock(&cd->hash_lock);
}