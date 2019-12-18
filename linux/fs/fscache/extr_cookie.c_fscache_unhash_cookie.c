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
struct hlist_bl_head {int dummy; } ;
struct fscache_cookie {int key_hash; int /*<<< orphan*/  hash_link; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct hlist_bl_head*) ; 
 struct hlist_bl_head* fscache_cookie_hash ; 
 int /*<<< orphan*/  hlist_bl_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_bl_lock (struct hlist_bl_head*) ; 
 int /*<<< orphan*/  hlist_bl_unlock (struct hlist_bl_head*) ; 

__attribute__((used)) static void fscache_unhash_cookie(struct fscache_cookie *cookie)
{
	struct hlist_bl_head *h;
	unsigned int bucket;

	bucket = cookie->key_hash & (ARRAY_SIZE(fscache_cookie_hash) - 1);
	h = &fscache_cookie_hash[bucket];

	hlist_bl_lock(h);
	hlist_bl_del(&cookie->hash_link);
	hlist_bl_unlock(h);
}