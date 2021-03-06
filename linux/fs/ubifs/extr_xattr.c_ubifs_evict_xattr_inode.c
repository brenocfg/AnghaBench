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
struct ubifs_info {int /*<<< orphan*/  vfs_sb; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 struct inode* ilookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 

void ubifs_evict_xattr_inode(struct ubifs_info *c, ino_t xattr_inum)
{
	struct inode *inode;

	inode = ilookup(c->vfs_sb, xattr_inum);
	if (inode) {
		clear_nlink(inode);
		iput(inode);
	}
}