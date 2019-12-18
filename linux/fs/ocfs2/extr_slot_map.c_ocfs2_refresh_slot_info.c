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
struct ocfs2_super {int /*<<< orphan*/  osb_lock; struct ocfs2_slot_info* slot_info; } ;
struct ocfs2_slot_info {scalar_t__ si_blocks; int /*<<< orphan*/ * si_bh; int /*<<< orphan*/  si_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INODE_CACHE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCFS2_BH_IGNORE_CACHE ; 
 int ocfs2_read_blocks (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_update_slot_info (struct ocfs2_slot_info*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ocfs2_refresh_slot_info (scalar_t__) ; 

int ocfs2_refresh_slot_info(struct ocfs2_super *osb)
{
	int ret;
	struct ocfs2_slot_info *si = osb->slot_info;

	if (si == NULL)
		return 0;

	BUG_ON(si->si_blocks == 0);
	BUG_ON(si->si_bh == NULL);

	trace_ocfs2_refresh_slot_info(si->si_blocks);

	/*
	 * We pass -1 as blocknr because we expect all of si->si_bh to
	 * be !NULL.  Thus, ocfs2_read_blocks() will ignore blocknr.  If
	 * this is not true, the read of -1 (UINT64_MAX) will fail.
	 */
	ret = ocfs2_read_blocks(INODE_CACHE(si->si_inode), -1, si->si_blocks,
				si->si_bh, OCFS2_BH_IGNORE_CACHE, NULL);
	if (ret == 0) {
		spin_lock(&osb->osb_lock);
		ocfs2_update_slot_info(si);
		spin_unlock(&osb->osb_lock);
	}

	return ret;
}