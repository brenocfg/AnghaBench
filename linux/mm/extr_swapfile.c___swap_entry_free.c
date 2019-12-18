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
struct swap_info_struct {int dummy; } ;
struct swap_cluster_info {int dummy; } ;

/* Variables and functions */
 unsigned char __swap_entry_free_locked (struct swap_info_struct*,unsigned long,unsigned char) ; 
 int /*<<< orphan*/  free_swap_slot (int /*<<< orphan*/ ) ; 
 struct swap_cluster_info* lock_cluster_or_swap_info (struct swap_info_struct*,unsigned long) ; 
 unsigned long swp_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_cluster_or_swap_info (struct swap_info_struct*,struct swap_cluster_info*) ; 

__attribute__((used)) static unsigned char __swap_entry_free(struct swap_info_struct *p,
				       swp_entry_t entry, unsigned char usage)
{
	struct swap_cluster_info *ci;
	unsigned long offset = swp_offset(entry);

	ci = lock_cluster_or_swap_info(p, offset);
	usage = __swap_entry_free_locked(p, offset, usage);
	unlock_cluster_or_swap_info(p, ci);
	if (!usage)
		free_swap_slot(entry);

	return usage;
}