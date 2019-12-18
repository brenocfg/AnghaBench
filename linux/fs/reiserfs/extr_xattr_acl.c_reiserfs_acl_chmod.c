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
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 scalar_t__ IS_PRIVATE (struct inode*) ; 
 scalar_t__ STAT_DATA_V1 ; 
 scalar_t__ get_inode_sd_version (struct inode*) ; 
 int posix_acl_chmod (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_posixacl (int /*<<< orphan*/ ) ; 

int reiserfs_acl_chmod(struct inode *inode)
{
	if (IS_PRIVATE(inode))
		return 0;
	if (get_inode_sd_version(inode) == STAT_DATA_V1 ||
	    !reiserfs_posixacl(inode->i_sb))
		return 0;

	return posix_acl_chmod(inode, inode->i_mode);
}