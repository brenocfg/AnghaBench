#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_lock; int /*<<< orphan*/  i_dentry; } ;
struct TYPE_4__ {int /*<<< orphan*/  d_alias; } ;
struct dentry {int /*<<< orphan*/  d_lock; int /*<<< orphan*/  d_seq; TYPE_2__ d_u; TYPE_1__* d_parent; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  __d_lookup_done (struct dentry*) ; 
 int /*<<< orphan*/  __d_rehash (struct dentry*) ; 
 int /*<<< orphan*/  __d_set_inode_and_type (struct dentry*,struct inode*,unsigned int) ; 
 unsigned int d_flags_for_inode (struct inode*) ; 
 int /*<<< orphan*/  d_in_lookup (struct dentry*) ; 
 int /*<<< orphan*/  end_dir_add (struct inode*,unsigned int) ; 
 int /*<<< orphan*/  fsnotify_update_flags (struct dentry*) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_write_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_write_seqcount_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 unsigned int start_dir_add (struct inode*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __d_add(struct dentry *dentry, struct inode *inode)
{
	struct inode *dir = NULL;
	unsigned n;
	spin_lock(&dentry->d_lock);
	if (unlikely(d_in_lookup(dentry))) {
		dir = dentry->d_parent->d_inode;
		n = start_dir_add(dir);
		__d_lookup_done(dentry);
	}
	if (inode) {
		unsigned add_flags = d_flags_for_inode(inode);
		hlist_add_head(&dentry->d_u.d_alias, &inode->i_dentry);
		raw_write_seqcount_begin(&dentry->d_seq);
		__d_set_inode_and_type(dentry, inode, add_flags);
		raw_write_seqcount_end(&dentry->d_seq);
		fsnotify_update_flags(dentry);
	}
	__d_rehash(dentry);
	if (dir)
		end_dir_add(dir, n);
	spin_unlock(&dentry->d_lock);
	if (inode)
		spin_unlock(&inode->i_lock);
}