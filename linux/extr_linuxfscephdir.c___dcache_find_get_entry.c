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
typedef  int u64 ;
struct inode {int /*<<< orphan*/  i_data; } ;
struct dentry {int /*<<< orphan*/  d_lockref; int /*<<< orphan*/  d_lock; } ;
struct ceph_readdir_cache_control {int index; struct dentry** dentries; int /*<<< orphan*/  page; } ;
typedef  scalar_t__ pgoff_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 scalar_t__ ceph_dir_is_complete_ordered (struct inode*) ; 
 int /*<<< orphan*/  ceph_readdir_cache_release (struct ceph_readdir_cache_control*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dout (char*,scalar_t__) ; 
 int /*<<< orphan*/  find_lock_page (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 struct dentry** kmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockref_get_not_dead (int /*<<< orphan*/ *) ; 
 scalar_t__ page_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *
__dcache_find_get_entry(struct dentry *parent, u64 idx,
			struct ceph_readdir_cache_control *cache_ctl)
{
	struct inode *dir = d_inode(parent);
	struct dentry *dentry;
	unsigned idx_mask = (PAGE_SIZE / sizeof(struct dentry *)) - 1;
	loff_t ptr_pos = idx * sizeof(struct dentry *);
	pgoff_t ptr_pgoff = ptr_pos >> PAGE_SHIFT;

	if (ptr_pos >= i_size_read(dir))
		return NULL;

	if (!cache_ctl->page || ptr_pgoff != page_index(cache_ctl->page)) {
		ceph_readdir_cache_release(cache_ctl);
		cache_ctl->page = find_lock_page(&dir->i_data, ptr_pgoff);
		if (!cache_ctl->page) {
			dout(" page %lu not found\n", ptr_pgoff);
			return ERR_PTR(-EAGAIN);
		}
		/* reading/filling the cache are serialized by
		   i_mutex, no need to use page lock */
		unlock_page(cache_ctl->page);
		cache_ctl->dentries = kmap(cache_ctl->page);
	}

	cache_ctl->index = idx & idx_mask;

	rcu_read_lock();
	spin_lock(&parent->d_lock);
	/* check i_size again here, because empty directory can be
	 * marked as complete while not holding the i_mutex. */
	if (ceph_dir_is_complete_ordered(dir) && ptr_pos < i_size_read(dir))
		dentry = cache_ctl->dentries[cache_ctl->index];
	else
		dentry = NULL;
	spin_unlock(&parent->d_lock);
	if (dentry && !lockref_get_not_dead(&dentry->d_lockref))
		dentry = NULL;
	rcu_read_unlock();
	return dentry ? : ERR_PTR(-EAGAIN);
}