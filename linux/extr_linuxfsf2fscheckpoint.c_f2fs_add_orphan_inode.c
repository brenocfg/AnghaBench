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
struct inode {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  ORPHAN_INO ; 
 int /*<<< orphan*/  __add_ino_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_update_inode_page (struct inode*) ; 

void f2fs_add_orphan_inode(struct inode *inode)
{
	/* add new orphan ino entry into list */
	__add_ino_entry(F2FS_I_SB(inode), inode->i_ino, 0, ORPHAN_INO);
	f2fs_update_inode_page(inode);
}