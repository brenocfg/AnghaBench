#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_super {int max_slots; int /*<<< orphan*/  osb_lock; struct ocfs2_slot_info* slot_info; } ;
struct ocfs2_slot_info {TYPE_1__* si_slots; } ;
struct TYPE_2__ {unsigned int sl_node_num; int /*<<< orphan*/  sl_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOENT ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 

int ocfs2_slot_to_node_num_locked(struct ocfs2_super *osb, int slot_num,
				  unsigned int *node_num)
{
	struct ocfs2_slot_info *si = osb->slot_info;

	assert_spin_locked(&osb->osb_lock);

	BUG_ON(slot_num < 0);
	BUG_ON(slot_num >= osb->max_slots);

	if (!si->si_slots[slot_num].sl_valid)
		return -ENOENT;

	*node_num = si->si_slots[slot_num].sl_node_num;
	return 0;
}