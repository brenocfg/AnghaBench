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
struct qstr {int dummy; } ;
struct inode {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_initxattrs ; 
 int security_inode_init_security (struct inode*,struct inode*,struct qstr const*,int /*<<< orphan*/ *,struct btrfs_trans_handle*) ; 

int btrfs_xattr_security_init(struct btrfs_trans_handle *trans,
			      struct inode *inode, struct inode *dir,
			      const struct qstr *qstr)
{
	return security_inode_init_security(inode, dir, qstr,
					    &btrfs_initxattrs, trans);
}