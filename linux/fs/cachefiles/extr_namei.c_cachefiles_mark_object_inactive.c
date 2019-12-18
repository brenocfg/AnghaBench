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
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
struct cachefiles_object {int /*<<< orphan*/  flags; int /*<<< orphan*/  active_node; struct dentry* dentry; } ;
struct cachefiles_cache {int /*<<< orphan*/  f_released; int /*<<< orphan*/  b_released; int /*<<< orphan*/  active_lock; int /*<<< orphan*/  active_nodes; } ;
typedef  int /*<<< orphan*/  blkcnt_t ;

/* Variables and functions */
 int /*<<< orphan*/  CACHEFILES_OBJECT_ACTIVE ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cachefiles_state_changed (struct cachefiles_cache*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct inode* d_backing_inode (struct dentry*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_cachefiles_mark_inactive (struct cachefiles_object*,struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void cachefiles_mark_object_inactive(struct cachefiles_cache *cache,
				     struct cachefiles_object *object,
				     blkcnt_t i_blocks)
{
	struct dentry *dentry = object->dentry;
	struct inode *inode = d_backing_inode(dentry);

	trace_cachefiles_mark_inactive(object, dentry, inode);

	write_lock(&cache->active_lock);
	rb_erase(&object->active_node, &cache->active_nodes);
	clear_bit(CACHEFILES_OBJECT_ACTIVE, &object->flags);
	write_unlock(&cache->active_lock);

	wake_up_bit(&object->flags, CACHEFILES_OBJECT_ACTIVE);

	/* This object can now be culled, so we need to let the daemon know
	 * that there is something it can remove if it needs to.
	 */
	atomic_long_add(i_blocks, &cache->b_released);
	if (atomic_inc_return(&cache->f_released))
		cachefiles_state_changed(cache);
}