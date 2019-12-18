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
typedef  scalar_t__ u32 ;
struct tipc_name_seq {scalar_t__ lower; scalar_t__ upper; } ;

/* Variables and functions */

int tipc_sub_check_overlap(struct tipc_name_seq *seq, u32 found_lower,
			   u32 found_upper)
{
	if (found_lower < seq->lower)
		found_lower = seq->lower;
	if (found_upper > seq->upper)
		found_upper = seq->upper;
	if (found_lower > found_upper)
		return 0;
	return 1;
}