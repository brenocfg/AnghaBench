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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ ONE_FP ; 
 int __fls (unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,unsigned int,int) ; 

__attribute__((used)) static int qfq_calc_index(u32 inv_w, unsigned int maxlen, u32 min_slot_shift)
{
	u64 slot_size = (u64)maxlen * inv_w;
	unsigned long size_map;
	int index = 0;

	size_map = slot_size >> min_slot_shift;
	if (!size_map)
		goto out;

	index = __fls(size_map) + 1;	/* basically a log_2 */
	index -= !(slot_size - (1ULL << (index + min_slot_shift - 1)));

	if (index < 0)
		index = 0;
out:
	pr_debug("qfq calc_index: W = %lu, L = %u, I = %d\n",
		 (unsigned long) ONE_FP/inv_w, maxlen, index);

	return index;
}