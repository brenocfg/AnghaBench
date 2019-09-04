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
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_HT_INODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int I_DIRTY_TIME ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 

void ext4_dirty_inode(struct inode *inode, int flags)
{
	handle_t *handle;

	if (flags == I_DIRTY_TIME)
		return;
	handle = ext4_journal_start(inode, EXT4_HT_INODE, 2);
	if (IS_ERR(handle))
		goto out;

	ext4_mark_inode_dirty(handle, inode);

	ext4_journal_stop(handle);
out:
	return;
}