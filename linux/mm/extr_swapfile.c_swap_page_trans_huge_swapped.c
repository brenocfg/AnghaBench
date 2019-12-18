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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct swap_info_struct {unsigned char* swap_map; } ;
struct swap_cluster_info {int dummy; } ;

/* Variables and functions */
 int SWAPFILE_CLUSTER ; 
 int /*<<< orphan*/  cluster_is_huge (struct swap_cluster_info*) ; 
 struct swap_cluster_info* lock_cluster_or_swap_info (struct swap_info_struct*,unsigned long) ; 
 unsigned long round_down (unsigned long,int) ; 
 scalar_t__ swap_count (unsigned char) ; 
 unsigned long swp_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_cluster_or_swap_info (struct swap_info_struct*,struct swap_cluster_info*) ; 

__attribute__((used)) static bool swap_page_trans_huge_swapped(struct swap_info_struct *si,
					 swp_entry_t entry)
{
	struct swap_cluster_info *ci;
	unsigned char *map = si->swap_map;
	unsigned long roffset = swp_offset(entry);
	unsigned long offset = round_down(roffset, SWAPFILE_CLUSTER);
	int i;
	bool ret = false;

	ci = lock_cluster_or_swap_info(si, offset);
	if (!ci || !cluster_is_huge(ci)) {
		if (swap_count(map[roffset]))
			ret = true;
		goto unlock_out;
	}
	for (i = 0; i < SWAPFILE_CLUSTER; i++) {
		if (swap_count(map[offset + i])) {
			ret = true;
			break;
		}
	}
unlock_out:
	unlock_cluster_or_swap_info(si, ci);
	return ret;
}