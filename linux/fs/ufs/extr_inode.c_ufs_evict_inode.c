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
struct inode {int /*<<< orphan*/  i_mode; scalar_t__ i_blocks; scalar_t__ i_size; int /*<<< orphan*/  i_data; int /*<<< orphan*/  i_nlink; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  inode_needs_sync (struct inode*) ; 
 int /*<<< orphan*/  invalidate_inode_buffers (struct inode*) ; 
 int /*<<< orphan*/  is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  truncate_inode_pages_final (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ufs_free_inode (struct inode*) ; 
 int /*<<< orphan*/  ufs_truncate_blocks (struct inode*) ; 
 int /*<<< orphan*/  ufs_update_inode (struct inode*,int /*<<< orphan*/ ) ; 

void ufs_evict_inode(struct inode * inode)
{
	int want_delete = 0;

	if (!inode->i_nlink && !is_bad_inode(inode))
		want_delete = 1;

	truncate_inode_pages_final(&inode->i_data);
	if (want_delete) {
		inode->i_size = 0;
		if (inode->i_blocks &&
		    (S_ISREG(inode->i_mode) || S_ISDIR(inode->i_mode) ||
		     S_ISLNK(inode->i_mode)))
			ufs_truncate_blocks(inode);
		ufs_update_inode(inode, inode_needs_sync(inode));
	}

	invalidate_inode_buffers(inode);
	clear_inode(inode);

	if (want_delete)
		ufs_free_inode(inode);
}