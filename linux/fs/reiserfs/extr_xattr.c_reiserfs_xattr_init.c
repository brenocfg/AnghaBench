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
struct super_block {int /*<<< orphan*/  s_flags; int /*<<< orphan*/  s_xattr; struct dentry* s_root; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_mount_opt; struct dentry* xattr_root; struct dentry* priv_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  REISERFS_POSIXACL ; 
 TYPE_1__* REISERFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  REISERFS_XATTRS_USER ; 
 int /*<<< orphan*/  SB_POSIXACL ; 
 int SB_RDONLY ; 
 int /*<<< orphan*/  XAROOT_NAME ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int create_privroot (struct dentry*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_negative (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 struct dentry* lookup_one_len (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 
 scalar_t__ reiserfs_posixacl (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_xattr_handlers ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int xattr_mount_check (struct super_block*) ; 

int reiserfs_xattr_init(struct super_block *s, int mount_flags)
{
	int err = 0;
	struct dentry *privroot = REISERFS_SB(s)->priv_root;

	err = xattr_mount_check(s);
	if (err)
		goto error;

	if (d_really_is_negative(privroot) && !(mount_flags & SB_RDONLY)) {
		inode_lock(d_inode(s->s_root));
		err = create_privroot(REISERFS_SB(s)->priv_root);
		inode_unlock(d_inode(s->s_root));
	}

	if (d_really_is_positive(privroot)) {
		s->s_xattr = reiserfs_xattr_handlers;
		inode_lock(d_inode(privroot));
		if (!REISERFS_SB(s)->xattr_root) {
			struct dentry *dentry;

			dentry = lookup_one_len(XAROOT_NAME, privroot,
						strlen(XAROOT_NAME));
			if (!IS_ERR(dentry))
				REISERFS_SB(s)->xattr_root = dentry;
			else
				err = PTR_ERR(dentry);
		}
		inode_unlock(d_inode(privroot));
	}

error:
	if (err) {
		clear_bit(REISERFS_XATTRS_USER, &REISERFS_SB(s)->s_mount_opt);
		clear_bit(REISERFS_POSIXACL, &REISERFS_SB(s)->s_mount_opt);
	}

	/* The super_block SB_POSIXACL must mirror the (no)acl mount option. */
	if (reiserfs_posixacl(s))
		s->s_flags |= SB_POSIXACL;
	else
		s->s_flags &= ~SB_POSIXACL;

	return err;
}