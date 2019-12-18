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
struct reiserfs_security_handle {scalar_t__ length; int /*<<< orphan*/ * value; int /*<<< orphan*/ * name; } ;
struct qstr {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_flags; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ IS_PRIVATE (struct inode*) ; 
 TYPE_1__* REISERFS_I (struct inode*) ; 
 int /*<<< orphan*/  i_has_xattr_dir ; 
 int reiserfs_xattr_jcreate_nblocks (struct inode*) ; 
 int reiserfs_xattr_nblocks (struct inode*,scalar_t__) ; 
 scalar_t__ reiserfs_xattrs_initialized (int /*<<< orphan*/ ) ; 
 int security_old_inode_init_security (struct inode*,struct inode*,struct qstr const*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,scalar_t__*) ; 

int reiserfs_security_init(struct inode *dir, struct inode *inode,
			   const struct qstr *qstr,
			   struct reiserfs_security_handle *sec)
{
	int blocks = 0;
	int error;

	sec->name = NULL;

	/* Don't add selinux attributes on xattrs - they'll never get used */
	if (IS_PRIVATE(dir))
		return 0;

	error = security_old_inode_init_security(inode, dir, qstr, &sec->name,
						 &sec->value, &sec->length);
	if (error) {
		if (error == -EOPNOTSUPP)
			error = 0;

		sec->name = NULL;
		sec->value = NULL;
		sec->length = 0;
		return error;
	}

	if (sec->length && reiserfs_xattrs_initialized(inode->i_sb)) {
		blocks = reiserfs_xattr_jcreate_nblocks(inode) +
			 reiserfs_xattr_nblocks(inode, sec->length);
		/* We don't want to count the directories twice if we have
		 * a default ACL. */
		REISERFS_I(inode)->i_flags |= i_has_xattr_dir;
	}
	return blocks;
}