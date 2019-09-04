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
struct inode {int i_state; int /*<<< orphan*/  i_lock; int /*<<< orphan*/  i_count; scalar_t__ i_nlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int I_CLEAR ; 
 int I_DIRTY_TIME ; 
 scalar_t__ atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput_final (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty_sync (struct inode*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_writeback_lazytime_iput (struct inode*) ; 

void iput(struct inode *inode)
{
	if (!inode)
		return;
	BUG_ON(inode->i_state & I_CLEAR);
retry:
	if (atomic_dec_and_lock(&inode->i_count, &inode->i_lock)) {
		if (inode->i_nlink && (inode->i_state & I_DIRTY_TIME)) {
			atomic_inc(&inode->i_count);
			spin_unlock(&inode->i_lock);
			trace_writeback_lazytime_iput(inode);
			mark_inode_dirty_sync(inode);
			goto retry;
		}
		iput_final(inode);
	}
}