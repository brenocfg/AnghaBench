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
typedef  size_t pgoff_t ;

/* Variables and functions */
 struct swap_info_struct* get_swap_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_swap_device (struct swap_info_struct*) ; 
 int swap_count (int /*<<< orphan*/ ) ; 
 size_t swp_offset (int /*<<< orphan*/ ) ; 

int __swap_count(swp_entry_t entry)
{
	struct swap_info_struct *si;
	pgoff_t offset = swp_offset(entry);
	int count = 0;

	si = get_swap_device(entry);
	if (si) {
		count = swap_count(si->swap_map[offset]);
		put_swap_device(si);
	}
	return count;
}