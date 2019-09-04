#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {TYPE_2__* s_root; } ;
struct inode {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  d_alias; } ;
struct TYPE_6__ {int /*<<< orphan*/  d_lock; TYPE_1__ d_u; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_3__* d_inode (TYPE_2__*) ; 
 TYPE_2__* d_make_root (struct inode*) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ihold (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs_superblock_set_dummy_root(struct super_block *sb, struct inode *inode)
{
	/* The mntroot acts as the dummy root dentry for this superblock */
	if (sb->s_root == NULL) {
		sb->s_root = d_make_root(inode);
		if (sb->s_root == NULL)
			return -ENOMEM;
		ihold(inode);
		/*
		 * Ensure that this dentry is invisible to d_find_alias().
		 * Otherwise, it may be spliced into the tree by
		 * d_splice_alias if a parent directory from the same
		 * filesystem gets mounted at a later time.
		 * This again causes shrink_dcache_for_umount_subtree() to
		 * Oops, since the test for IS_ROOT() will fail.
		 */
		spin_lock(&d_inode(sb->s_root)->i_lock);
		spin_lock(&sb->s_root->d_lock);
		hlist_del_init(&sb->s_root->d_u.d_alias);
		spin_unlock(&sb->s_root->d_lock);
		spin_unlock(&d_inode(sb->s_root)->i_lock);
	}
	return 0;
}