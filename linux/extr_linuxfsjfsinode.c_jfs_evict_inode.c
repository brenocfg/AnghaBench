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
struct inode {int /*<<< orphan*/  i_data; int /*<<< orphan*/  i_nlink; } ;
struct TYPE_2__ {scalar_t__ fileset; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_Freewmap ; 
 scalar_t__ FILESYSTEM_I ; 
 TYPE_1__* JFS_IP (struct inode*) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  diFree (struct inode*) ; 
 int /*<<< orphan*/  dquot_drop (struct inode*) ; 
 int /*<<< orphan*/  dquot_free_inode (struct inode*) ; 
 int /*<<< orphan*/  dquot_initialize (struct inode*) ; 
 int /*<<< orphan*/  is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  jfs_free_zero_link (struct inode*) ; 
 int /*<<< orphan*/  jfs_info (char*,struct inode*) ; 
 scalar_t__ test_cflag (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  truncate_inode_pages_final (int /*<<< orphan*/ *) ; 

void jfs_evict_inode(struct inode *inode)
{
	jfs_info("In jfs_evict_inode, inode = 0x%p", inode);

	if (!inode->i_nlink && !is_bad_inode(inode)) {
		dquot_initialize(inode);

		if (JFS_IP(inode)->fileset == FILESYSTEM_I) {
			truncate_inode_pages_final(&inode->i_data);

			if (test_cflag(COMMIT_Freewmap, inode))
				jfs_free_zero_link(inode);

			diFree(inode);

			/*
			 * Free the inode from the quota allocation.
			 */
			dquot_initialize(inode);
			dquot_free_inode(inode);
		}
	} else {
		truncate_inode_pages_final(&inode->i_data);
	}
	clear_inode(inode);
	dquot_drop(inode);
}