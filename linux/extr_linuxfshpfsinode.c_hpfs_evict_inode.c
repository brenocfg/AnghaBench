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
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  hpfs_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_remove_fnode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  truncate_inode_pages_final (int /*<<< orphan*/ *) ; 

void hpfs_evict_inode(struct inode *inode)
{
	truncate_inode_pages_final(&inode->i_data);
	clear_inode(inode);
	if (!inode->i_nlink) {
		hpfs_lock(inode->i_sb);
		hpfs_remove_fnode(inode->i_sb, inode->i_ino);
		hpfs_unlock(inode->i_sb);
	}
}