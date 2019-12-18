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
struct ocfs2_slot_info {int si_num_slots; TYPE_1__* si_slots; } ;
struct TYPE_2__ {int sl_valid; unsigned int sl_node_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static void ocfs2_set_slot(struct ocfs2_slot_info *si,
			   int slot_num, unsigned int node_num)
{
	BUG_ON((slot_num < 0) || (slot_num >= si->si_num_slots));

	si->si_slots[slot_num].sl_valid = 1;
	si->si_slots[slot_num].sl_node_num = node_num;
}