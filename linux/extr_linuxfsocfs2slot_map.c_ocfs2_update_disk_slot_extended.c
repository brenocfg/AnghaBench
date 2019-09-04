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
struct ocfs2_slot_map_extended {TYPE_1__* se_slots; } ;
struct ocfs2_slot_info {int si_slots_per_block; int si_blocks; struct buffer_head** si_bh; TYPE_2__* si_slots; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  sl_node_num; scalar_t__ sl_valid; } ;
struct TYPE_3__ {int /*<<< orphan*/  es_node_num; scalar_t__ es_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_update_disk_slot_extended(struct ocfs2_slot_info *si,
					    int slot_num,
					    struct buffer_head **bh)
{
	int blkind = slot_num / si->si_slots_per_block;
	int slotno = slot_num % si->si_slots_per_block;
	struct ocfs2_slot_map_extended *se;

	BUG_ON(blkind >= si->si_blocks);

	se = (struct ocfs2_slot_map_extended *)si->si_bh[blkind]->b_data;
	se->se_slots[slotno].es_valid = si->si_slots[slot_num].sl_valid;
	if (si->si_slots[slot_num].sl_valid)
		se->se_slots[slotno].es_node_num =
			cpu_to_le32(si->si_slots[slot_num].sl_node_num);
	*bh = si->si_bh[blkind];
}