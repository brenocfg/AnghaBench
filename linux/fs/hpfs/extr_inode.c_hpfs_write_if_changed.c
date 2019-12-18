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
struct inode {int dummy; } ;
struct hpfs_inode_info {scalar_t__ i_dirty; } ;

/* Variables and functions */
 struct hpfs_inode_info* hpfs_i (struct inode*) ; 
 int /*<<< orphan*/  hpfs_write_inode (struct inode*) ; 

void hpfs_write_if_changed(struct inode *inode)
{
	struct hpfs_inode_info *hpfs_inode = hpfs_i(inode);

	if (hpfs_inode->i_dirty)
		hpfs_write_inode(inode);
}