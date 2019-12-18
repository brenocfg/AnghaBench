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
struct inode {int /*<<< orphan*/  i_dentry; } ;
struct TYPE_2__ {int /*<<< orphan*/  d_alias; } ;
struct dentry {int d_flags; int /*<<< orphan*/  d_lock; int /*<<< orphan*/  d_seq; TYPE_1__ d_u; } ;

/* Variables and functions */
 int DCACHE_LRU_LIST ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __d_set_inode_and_type (struct dentry*,struct inode*,unsigned int) ; 
 unsigned int d_flags_for_inode (struct inode*) ; 
 int /*<<< orphan*/  d_in_lookup (struct dentry*) ; 
 int /*<<< orphan*/  fsnotify_update_flags (struct dentry*) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nr_dentry_negative ; 
 int /*<<< orphan*/  raw_write_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_write_seqcount_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_dec (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __d_instantiate(struct dentry *dentry, struct inode *inode)
{
	unsigned add_flags = d_flags_for_inode(inode);
	WARN_ON(d_in_lookup(dentry));

	spin_lock(&dentry->d_lock);
	/*
	 * Decrement negative dentry count if it was in the LRU list.
	 */
	if (dentry->d_flags & DCACHE_LRU_LIST)
		this_cpu_dec(nr_dentry_negative);
	hlist_add_head(&dentry->d_u.d_alias, &inode->i_dentry);
	raw_write_seqcount_begin(&dentry->d_seq);
	__d_set_inode_and_type(dentry, inode, add_flags);
	raw_write_seqcount_end(&dentry->d_seq);
	fsnotify_update_flags(dentry);
	spin_unlock(&dentry->d_lock);
}