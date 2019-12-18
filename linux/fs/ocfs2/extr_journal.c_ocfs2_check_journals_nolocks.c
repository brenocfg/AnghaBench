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
struct ocfs2_super {unsigned int max_slots; int /*<<< orphan*/ * slot_recovery_generations; } ;
struct TYPE_3__ {int /*<<< orphan*/  ij_flags; } ;
struct TYPE_4__ {TYPE_1__ journal1; } ;
struct ocfs2_dinode {TYPE_2__ id1; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int EROFS ; 
 int OCFS2_JOURNAL_DIRTY_FL ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_get_recovery_generation (struct ocfs2_dinode*) ; 
 int ocfs2_read_journal_inode (struct ocfs2_super*,unsigned int,struct buffer_head**,int /*<<< orphan*/ *) ; 

int ocfs2_check_journals_nolocks(struct ocfs2_super *osb)
{
	int ret = 0;
	unsigned int slot;
	struct buffer_head *di_bh = NULL;
	struct ocfs2_dinode *di;
	int journal_dirty = 0;

	for(slot = 0; slot < osb->max_slots; slot++) {
		ret = ocfs2_read_journal_inode(osb, slot, &di_bh, NULL);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		di = (struct ocfs2_dinode *) di_bh->b_data;

		osb->slot_recovery_generations[slot] =
					ocfs2_get_recovery_generation(di);

		if (le32_to_cpu(di->id1.journal1.ij_flags) &
		    OCFS2_JOURNAL_DIRTY_FL)
			journal_dirty = 1;

		brelse(di_bh);
		di_bh = NULL;
	}

out:
	if (journal_dirty)
		ret = -EROFS;
	return ret;
}