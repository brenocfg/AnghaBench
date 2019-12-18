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
struct ocfs2_slot_map {void** sm_slots; } ;
struct ocfs2_slot_info {int si_num_slots; struct buffer_head** si_bh; TYPE_1__* si_slots; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  sl_node_num; scalar_t__ sl_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_INVALID_SLOT ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_update_disk_slot_old(struct ocfs2_slot_info *si,
				       int slot_num,
				       struct buffer_head **bh)
{
	int i;
	struct ocfs2_slot_map *sm;

	sm = (struct ocfs2_slot_map *)si->si_bh[0]->b_data;
	for (i = 0; i < si->si_num_slots; i++) {
		if (si->si_slots[i].sl_valid)
			sm->sm_slots[i] =
				cpu_to_le16(si->si_slots[i].sl_node_num);
		else
			sm->sm_slots[i] = cpu_to_le16(OCFS2_INVALID_SLOT);
	}
	*bh = si->si_bh[0];
}