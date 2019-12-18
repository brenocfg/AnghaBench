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
struct dentry {struct dentry* d_parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  debug_id; } ;
struct cachefiles_object {struct dentry* dentry; TYPE_1__ fscache; } ;
struct cachefiles_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct dentry*) ; 
 int /*<<< orphan*/  FSCACHE_OBJECT_KILLED_BY_CACHE ; 
 int /*<<< orphan*/  FSCACHE_OBJECT_WAS_RETIRED ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int cachefiles_bury_object (struct cachefiles_cache*,struct cachefiles_object*,struct dentry*,struct dentry*,int,int /*<<< orphan*/ ) ; 
 struct dentry* d_backing_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock_nested (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int cachefiles_delete_object(struct cachefiles_cache *cache,
			     struct cachefiles_object *object)
{
	struct dentry *dir;
	int ret;

	_enter(",OBJ%x{%p}", object->fscache.debug_id, object->dentry);

	ASSERT(object->dentry);
	ASSERT(d_backing_inode(object->dentry));
	ASSERT(object->dentry->d_parent);

	dir = dget_parent(object->dentry);

	inode_lock_nested(d_inode(dir), I_MUTEX_PARENT);

	if (test_bit(FSCACHE_OBJECT_KILLED_BY_CACHE, &object->fscache.flags)) {
		/* object allocation for the same key preemptively deleted this
		 * object's file so that it could create its own file */
		_debug("object preemptively buried");
		inode_unlock(d_inode(dir));
		ret = 0;
	} else {
		/* we need to check that our parent is _still_ our parent - it
		 * may have been renamed */
		if (dir == object->dentry->d_parent) {
			ret = cachefiles_bury_object(cache, object, dir,
						     object->dentry, false,
						     FSCACHE_OBJECT_WAS_RETIRED);
		} else {
			/* it got moved, presumably by cachefilesd culling it,
			 * so it's no longer in the key path and we can ignore
			 * it */
			inode_unlock(d_inode(dir));
			ret = 0;
		}
	}

	dput(dir);
	_leave(" = %d", ret);
	return ret;
}