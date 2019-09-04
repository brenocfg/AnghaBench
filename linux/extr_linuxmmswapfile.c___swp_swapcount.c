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
 struct swap_info_struct* __swap_info_get (int /*<<< orphan*/ ) ; 
 int swap_swapcount (struct swap_info_struct*,int /*<<< orphan*/ ) ; 

int __swp_swapcount(swp_entry_t entry)
{
	int count = 0;
	struct swap_info_struct *si;

	si = __swap_info_get(entry);
	if (si)
		count = swap_swapcount(si, entry);
	return count;
}