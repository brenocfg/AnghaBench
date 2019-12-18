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
struct nfs_access_entry {int /*<<< orphan*/  mask; int /*<<< orphan*/  cred; int /*<<< orphan*/  rb_node; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  access_cache_inode_lru; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  NFS_INO_ACL_LRU_SET ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_cred (int /*<<< orphan*/ ) ; 
 struct nfs_access_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_access_add_rbtree (struct inode*,struct nfs_access_entry*) ; 
 int /*<<< orphan*/  nfs_access_cache_enforce_limit () ; 
 int /*<<< orphan*/  nfs_access_lru_list ; 
 int /*<<< orphan*/  nfs_access_lru_lock ; 
 int /*<<< orphan*/  nfs_access_nr_entries ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nfs_access_add_cache(struct inode *inode, struct nfs_access_entry *set)
{
	struct nfs_access_entry *cache = kmalloc(sizeof(*cache), GFP_KERNEL);
	if (cache == NULL)
		return;
	RB_CLEAR_NODE(&cache->rb_node);
	cache->cred = get_cred(set->cred);
	cache->mask = set->mask;

	/* The above field assignments must be visible
	 * before this item appears on the lru.  We cannot easily
	 * use rcu_assign_pointer, so just force the memory barrier.
	 */
	smp_wmb();
	nfs_access_add_rbtree(inode, cache);

	/* Update accounting */
	smp_mb__before_atomic();
	atomic_long_inc(&nfs_access_nr_entries);
	smp_mb__after_atomic();

	/* Add inode to global LRU list */
	if (!test_bit(NFS_INO_ACL_LRU_SET, &NFS_I(inode)->flags)) {
		spin_lock(&nfs_access_lru_lock);
		if (!test_and_set_bit(NFS_INO_ACL_LRU_SET, &NFS_I(inode)->flags))
			list_add_tail(&NFS_I(inode)->access_cache_inode_lru,
					&nfs_access_lru_list);
		spin_unlock(&nfs_access_lru_lock);
	}
	nfs_access_cache_enforce_limit();
}