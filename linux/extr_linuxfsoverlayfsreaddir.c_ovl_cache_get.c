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
struct ovl_dir_cache {scalar_t__ version; int refcount; int /*<<< orphan*/  entries; int /*<<< orphan*/  root; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ovl_dir_cache* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  kfree (struct ovl_dir_cache*) ; 
 struct ovl_dir_cache* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_cache_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ovl_dentry_version_get (struct dentry*) ; 
 struct ovl_dir_cache* ovl_dir_cache (int /*<<< orphan*/ ) ; 
 int ovl_dir_read_merged (struct dentry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ovl_set_dir_cache (int /*<<< orphan*/ ,struct ovl_dir_cache*) ; 

__attribute__((used)) static struct ovl_dir_cache *ovl_cache_get(struct dentry *dentry)
{
	int res;
	struct ovl_dir_cache *cache;

	cache = ovl_dir_cache(d_inode(dentry));
	if (cache && ovl_dentry_version_get(dentry) == cache->version) {
		WARN_ON(!cache->refcount);
		cache->refcount++;
		return cache;
	}
	ovl_set_dir_cache(d_inode(dentry), NULL);

	cache = kzalloc(sizeof(struct ovl_dir_cache), GFP_KERNEL);
	if (!cache)
		return ERR_PTR(-ENOMEM);

	cache->refcount = 1;
	INIT_LIST_HEAD(&cache->entries);
	cache->root = RB_ROOT;

	res = ovl_dir_read_merged(dentry, &cache->entries, &cache->root);
	if (res) {
		ovl_cache_free(&cache->entries);
		kfree(cache);
		return ERR_PTR(res);
	}

	cache->version = ovl_dentry_version_get(dentry);
	ovl_set_dir_cache(d_inode(dentry), cache);

	return cache;
}