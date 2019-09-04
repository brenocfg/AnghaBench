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
struct super_block {int /*<<< orphan*/  s_fsnotify_inode_refs; } ;
struct inode {struct super_block* i_sb; } ;

/* Variables and functions */
 unsigned int FSNOTIFY_OBJ_TYPE_INODE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ atomic_long_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  wake_up_var (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fsnotify_drop_object(unsigned int type, void *objp)
{
	struct inode *inode;
	struct super_block *sb;

	if (!objp)
		return;
	/* Currently only inode references are passed to be dropped */
	if (WARN_ON_ONCE(type != FSNOTIFY_OBJ_TYPE_INODE))
		return;
	inode = objp;
	sb = inode->i_sb;
	iput(inode);
	if (atomic_long_dec_and_test(&sb->s_fsnotify_inode_refs))
		wake_up_var(&sb->s_fsnotify_inode_refs);
}