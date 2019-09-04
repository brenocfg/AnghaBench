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
struct ocfs2_super {struct ocfs2_slot_info* slot_info; int /*<<< orphan*/  osb_lock; } ;
struct ocfs2_slot_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocfs2_invalidate_slot (struct ocfs2_slot_info*,int) ; 
 int ocfs2_update_disk_slot (struct ocfs2_super*,struct ocfs2_slot_info*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ocfs2_clear_slot(struct ocfs2_super *osb, int slot_num)
{
	struct ocfs2_slot_info *si = osb->slot_info;

	if (si == NULL)
		return 0;

	spin_lock(&osb->osb_lock);
	ocfs2_invalidate_slot(si, slot_num);
	spin_unlock(&osb->osb_lock);

	return ocfs2_update_disk_slot(osb, osb->slot_info, slot_num);
}