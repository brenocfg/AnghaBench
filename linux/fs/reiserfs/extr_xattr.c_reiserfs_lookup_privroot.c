#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {struct dentry* s_root; } ;
struct dentry {int dummy; } ;
struct TYPE_6__ {struct dentry* priv_root; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  PRIVROOT_NAME ; 
 int PTR_ERR (struct dentry*) ; 
 TYPE_4__* REISERFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  S_PRIVATE ; 
 TYPE_1__* d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int /*<<< orphan*/  d_set_d_op (struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  inode_unlock (TYPE_1__*) ; 
 struct dentry* lookup_one_len (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xattr_lookup_poison_ops ; 

int reiserfs_lookup_privroot(struct super_block *s)
{
	struct dentry *dentry;
	int err = 0;

	/* If we don't have the privroot located yet - go find it */
	inode_lock(d_inode(s->s_root));
	dentry = lookup_one_len(PRIVROOT_NAME, s->s_root,
				strlen(PRIVROOT_NAME));
	if (!IS_ERR(dentry)) {
		REISERFS_SB(s)->priv_root = dentry;
		d_set_d_op(dentry, &xattr_lookup_poison_ops);
		if (d_really_is_positive(dentry))
			d_inode(dentry)->i_flags |= S_PRIVATE;
	} else
		err = PTR_ERR(dentry);
	inode_unlock(d_inode(s->s_root));

	return err;
}