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
struct dentry {int dummy; } ;
struct cachefiles_cache {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ESTALE ; 
 int /*<<< orphan*/  FSCACHE_OBJECT_WAS_CULLED ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  _debug (char*,...) ; 
 int /*<<< orphan*/  _enter (char*,struct dentry*,char*) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int cachefiles_bury_object (struct cachefiles_cache*,int /*<<< orphan*/ *,struct dentry*,struct dentry*,int,int /*<<< orphan*/ ) ; 
 struct dentry* cachefiles_check_active (struct cachefiles_cache*,struct dentry*,char*) ; 
 int cachefiles_remove_object_xattr (struct cachefiles_cache*,struct dentry*) ; 
 scalar_t__ d_backing_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

int cachefiles_cull(struct cachefiles_cache *cache, struct dentry *dir,
		    char *filename)
{
	struct dentry *victim;
	int ret;

	_enter(",%pd/,%s", dir, filename);

	victim = cachefiles_check_active(cache, dir, filename);
	if (IS_ERR(victim))
		return PTR_ERR(victim);

	_debug("victim -> %p %s",
	       victim, d_backing_inode(victim) ? "positive" : "negative");

	/* okay... the victim is not being used so we can cull it
	 * - start by marking it as stale
	 */
	_debug("victim is cullable");

	ret = cachefiles_remove_object_xattr(cache, victim);
	if (ret < 0)
		goto error_unlock;

	/*  actually remove the victim (drops the dir mutex) */
	_debug("bury");

	ret = cachefiles_bury_object(cache, NULL, dir, victim, false,
				     FSCACHE_OBJECT_WAS_CULLED);
	if (ret < 0)
		goto error;

	dput(victim);
	_leave(" = 0");
	return 0;

error_unlock:
	inode_unlock(d_inode(dir));
error:
	dput(victim);
	if (ret == -ENOENT) {
		/* file or dir now absent - probably retired by netfs */
		_leave(" = -ESTALE [absent]");
		return -ESTALE;
	}

	if (ret != -ENOMEM) {
		pr_err("Internal error: %d\n", ret);
		ret = -EIO;
	}

	_leave(" = %d", ret);
	return ret;
}