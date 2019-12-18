#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int i_state; TYPE_1__* i_mapping; int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_datasync_tid; } ;
struct TYPE_5__ {int /*<<< orphan*/ * s_journal; } ;
struct TYPE_4__ {int /*<<< orphan*/  private_list; } ;

/* Variables and functions */
 TYPE_3__* EXT4_I (struct inode*) ; 
 TYPE_2__* EXT4_SB (int /*<<< orphan*/ ) ; 
 int I_DIRTY_DATASYNC ; 
 int /*<<< orphan*/  jbd2_transaction_committed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ext4_inode_datasync_dirty(struct inode *inode)
{
	journal_t *journal = EXT4_SB(inode->i_sb)->s_journal;

	if (journal)
		return !jbd2_transaction_committed(journal,
					EXT4_I(inode)->i_datasync_tid);
	/* Any metadata buffers to write? */
	if (!list_empty(&inode->i_mapping->private_list))
		return true;
	return inode->i_state & I_DIRTY_DATASYNC;
}