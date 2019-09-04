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
typedef  scalar_t__ u64 ;
struct branch_type_stat {scalar_t__ branch_to; } ;

/* Variables and functions */
 int branch_from_str (char*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int branch_to_str (char*,int,scalar_t__,scalar_t__,scalar_t__,struct branch_type_stat*) ; 
 int scnprintf (char*,int,char*) ; 

__attribute__((used)) static int counts_str_build(char *bf, int bfsize,
			     u64 branch_count, u64 predicted_count,
			     u64 abort_count, u64 cycles_count,
			     u64 iter_count, u64 iter_cycles,
			     u64 from_count,
			     struct branch_type_stat *brtype_stat)
{
	int printed;

	if (branch_count == 0)
		return scnprintf(bf, bfsize, " (calltrace)");

	if (brtype_stat->branch_to) {
		printed = branch_to_str(bf, bfsize, branch_count,
				predicted_count, abort_count, brtype_stat);
	} else {
		printed = branch_from_str(bf, bfsize, branch_count,
				cycles_count, iter_count, iter_cycles,
				from_count);
	}

	if (!printed)
		bf[0] = 0;

	return printed;
}