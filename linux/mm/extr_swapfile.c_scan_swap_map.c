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

/* Variables and functions */
 int scan_swap_map_slots (struct swap_info_struct*,unsigned char,int,int /*<<< orphan*/ *) ; 
 unsigned long swp_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long scan_swap_map(struct swap_info_struct *si,
				   unsigned char usage)
{
	swp_entry_t entry;
	int n_ret;

	n_ret = scan_swap_map_slots(si, usage, 1, &entry);

	if (n_ret)
		return swp_offset(entry);
	else
		return 0;

}