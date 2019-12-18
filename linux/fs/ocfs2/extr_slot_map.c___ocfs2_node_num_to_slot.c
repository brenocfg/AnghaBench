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
struct TYPE_2__ {unsigned int sl_node_num; scalar_t__ sl_valid; } ;

/* Variables and functions */
 int ENOENT ; 

__attribute__((used)) static int __ocfs2_node_num_to_slot(struct ocfs2_slot_info *si,
				    unsigned int node_num)
{
	int i, ret = -ENOENT;

	for(i = 0; i < si->si_num_slots; i++) {
		if (si->si_slots[i].sl_valid &&
		    (node_num == si->si_slots[i].sl_node_num)) {
			ret = i;
			break;
		}
	}

	return ret;
}