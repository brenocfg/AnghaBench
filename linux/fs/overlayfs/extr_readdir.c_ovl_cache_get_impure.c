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
struct path {struct dentry* dentry; } ;
struct ovl_dir_cache {scalar_t__ version; int /*<<< orphan*/  entries; int /*<<< orphan*/  root; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ovl_dir_cache* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OVL_IMPURE ; 
 int /*<<< orphan*/  OVL_XATTR_IMPURE ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  kfree (struct ovl_dir_cache*) ; 
 struct ovl_dir_cache* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ovl_cache_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ovl_clear_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_dentry_upper (struct dentry*) ; 
 scalar_t__ ovl_dentry_version_get (struct dentry*) ; 
 struct ovl_dir_cache* ovl_dir_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_dir_cache_free (int /*<<< orphan*/ ) ; 
 int ovl_dir_read_impure (struct path*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ovl_do_removexattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_drop_write (struct dentry*) ; 
 int /*<<< orphan*/  ovl_set_dir_cache (int /*<<< orphan*/ ,struct ovl_dir_cache*) ; 
 int /*<<< orphan*/  ovl_want_write (struct dentry*) ; 

__attribute__((used)) static struct ovl_dir_cache *ovl_cache_get_impure(struct path *path)
{
	int res;
	struct dentry *dentry = path->dentry;
	struct ovl_dir_cache *cache;

	cache = ovl_dir_cache(d_inode(dentry));
	if (cache && ovl_dentry_version_get(dentry) == cache->version)
		return cache;

	/* Impure cache is not refcounted, free it here */
	ovl_dir_cache_free(d_inode(dentry));
	ovl_set_dir_cache(d_inode(dentry), NULL);

	cache = kzalloc(sizeof(struct ovl_dir_cache), GFP_KERNEL);
	if (!cache)
		return ERR_PTR(-ENOMEM);

	res = ovl_dir_read_impure(path, &cache->entries, &cache->root);
	if (res) {
		ovl_cache_free(&cache->entries);
		kfree(cache);
		return ERR_PTR(res);
	}
	if (list_empty(&cache->entries)) {
		/*
		 * A good opportunity to get rid of an unneeded "impure" flag.
		 * Removing the "impure" xattr is best effort.
		 */
		if (!ovl_want_write(dentry)) {
			ovl_do_removexattr(ovl_dentry_upper(dentry),
					   OVL_XATTR_IMPURE);
			ovl_drop_write(dentry);
		}
		ovl_clear_flag(OVL_IMPURE, d_inode(dentry));
		kfree(cache);
		return NULL;
	}

	cache->version = ovl_dentry_version_get(dentry);
	ovl_set_dir_cache(d_inode(dentry), cache);

	return cache;
}