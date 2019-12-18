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
struct ocfs2_super {int /*<<< orphan*/  osb_lock; } ;
struct ocfs2_slot_info {int /*<<< orphan*/  si_inode; scalar_t__ si_extended; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_update_disk_slot_extended (struct ocfs2_slot_info*,int,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_update_disk_slot_old (struct ocfs2_slot_info*,int,struct buffer_head**) ; 
 int ocfs2_write_block (struct ocfs2_super*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_update_disk_slot(struct ocfs2_super *osb,
				  struct ocfs2_slot_info *si,
				  int slot_num)
{
	int status;
	struct buffer_head *bh;

	spin_lock(&osb->osb_lock);
	if (si->si_extended)
		ocfs2_update_disk_slot_extended(si, slot_num, &bh);
	else
		ocfs2_update_disk_slot_old(si, slot_num, &bh);
	spin_unlock(&osb->osb_lock);

	status = ocfs2_write_block(osb, bh, INODE_CACHE(si->si_inode));
	if (status < 0)
		mlog_errno(status);

	return status;
}