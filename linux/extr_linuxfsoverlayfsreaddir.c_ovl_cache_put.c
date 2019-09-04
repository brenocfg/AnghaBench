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
struct ovl_dir_file {struct ovl_dir_cache* cache; } ;
struct ovl_dir_cache {scalar_t__ refcount; int /*<<< orphan*/  entries; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  kfree (struct ovl_dir_cache*) ; 
 int /*<<< orphan*/  ovl_cache_free (int /*<<< orphan*/ *) ; 
 struct ovl_dir_cache* ovl_dir_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_set_dir_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ovl_cache_put(struct ovl_dir_file *od, struct dentry *dentry)
{
	struct ovl_dir_cache *cache = od->cache;

	WARN_ON(cache->refcount <= 0);
	cache->refcount--;
	if (!cache->refcount) {
		if (ovl_dir_cache(d_inode(dentry)) == cache)
			ovl_set_dir_cache(d_inode(dentry), NULL);

		ovl_cache_free(&cache->entries);
		kfree(cache);
	}
}