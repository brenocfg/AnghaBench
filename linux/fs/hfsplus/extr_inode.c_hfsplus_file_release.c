#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct inode {int i_flags; int /*<<< orphan*/  i_ino; struct super_block* i_sb; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  opencnt; struct inode* rsrc_inode; } ;
struct TYPE_3__ {int /*<<< orphan*/  hidden_dir; } ;

/* Variables and functions */
 TYPE_2__* HFSPLUS_I (struct inode*) ; 
 scalar_t__ HFSPLUS_IS_RSRC (struct inode*) ; 
 TYPE_1__* HFSPLUS_SB (struct super_block*) ; 
 int S_DEAD ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfsplus_delete_cat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfsplus_delete_inode (struct inode*) ; 
 int /*<<< orphan*/  hfsplus_file_truncate (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 

__attribute__((used)) static int hfsplus_file_release(struct inode *inode, struct file *file)
{
	struct super_block *sb = inode->i_sb;

	if (HFSPLUS_IS_RSRC(inode))
		inode = HFSPLUS_I(inode)->rsrc_inode;
	if (atomic_dec_and_test(&HFSPLUS_I(inode)->opencnt)) {
		inode_lock(inode);
		hfsplus_file_truncate(inode);
		if (inode->i_flags & S_DEAD) {
			hfsplus_delete_cat(inode->i_ino,
					   HFSPLUS_SB(sb)->hidden_dir, NULL);
			hfsplus_delete_inode(inode);
		}
		inode_unlock(inode);
	}
	return 0;
}