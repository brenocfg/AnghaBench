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
struct posix_acl {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int __f2fs_set_acl (struct inode*,int,struct posix_acl*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_cp_error (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int f2fs_set_acl(struct inode *inode, struct posix_acl *acl, int type)
{
	if (unlikely(f2fs_cp_error(F2FS_I_SB(inode))))
		return -EIO;

	return __f2fs_set_acl(inode, type, acl, NULL);
}