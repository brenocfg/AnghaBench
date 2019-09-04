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
struct swap_info_struct {int /*<<< orphan*/ * swap_map; } ;
struct swap_cluster_info {int dummy; } ;
typedef  size_t pgoff_t ;

/* Variables and functions */
 struct swap_cluster_info* lock_cluster_or_swap_info (struct swap_info_struct*,size_t) ; 
 int swap_count (int /*<<< orphan*/ ) ; 
 size_t swp_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_cluster_or_swap_info (struct swap_info_struct*,struct swap_cluster_info*) ; 

__attribute__((used)) static int swap_swapcount(struct swap_info_struct *si, swp_entry_t entry)
{
	int count = 0;
	pgoff_t offset = swp_offset(entry);
	struct swap_cluster_info *ci;

	ci = lock_cluster_or_swap_info(si, offset);
	count = swap_count(si->swap_map[offset]);
	unlock_cluster_or_swap_info(si, ci);
	return count;
}