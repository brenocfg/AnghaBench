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
struct TYPE_3__ {int /*<<< orphan*/  d_alias; } ;
struct dentry {int /*<<< orphan*/  d_lock; TYPE_2__* d_sb; int /*<<< orphan*/  d_hash; TYPE_1__ d_u; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_roots; } ;

/* Variables and functions */
 unsigned int DCACHE_DISCONNECTED ; 
 struct dentry* __d_find_any_alias (struct inode*) ; 
 int /*<<< orphan*/  __d_set_inode_and_type (struct dentry*,struct inode*,unsigned int) ; 
 unsigned int d_flags_for_inode (struct inode*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_bl_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_bl_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_bl_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  security_d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dentry *__d_instantiate_anon(struct dentry *dentry,
					   struct inode *inode,
					   bool disconnected)
{
	struct dentry *res;
	unsigned add_flags;

	security_d_instantiate(dentry, inode);
	spin_lock(&inode->i_lock);
	res = __d_find_any_alias(inode);
	if (res) {
		spin_unlock(&inode->i_lock);
		dput(dentry);
		goto out_iput;
	}

	/* attach a disconnected dentry */
	add_flags = d_flags_for_inode(inode);

	if (disconnected)
		add_flags |= DCACHE_DISCONNECTED;

	spin_lock(&dentry->d_lock);
	__d_set_inode_and_type(dentry, inode, add_flags);
	hlist_add_head(&dentry->d_u.d_alias, &inode->i_dentry);
	if (!disconnected) {
		hlist_bl_lock(&dentry->d_sb->s_roots);
		hlist_bl_add_head(&dentry->d_hash, &dentry->d_sb->s_roots);
		hlist_bl_unlock(&dentry->d_sb->s_roots);
	}
	spin_unlock(&dentry->d_lock);
	spin_unlock(&inode->i_lock);

	return dentry;

 out_iput:
	iput(inode);
	return res;
}