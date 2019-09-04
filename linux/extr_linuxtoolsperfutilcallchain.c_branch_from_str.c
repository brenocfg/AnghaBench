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

/* Variables and functions */
 scalar_t__ count_pri64_printf (int /*<<< orphan*/ ,char*,int,char*,int) ; 
 scalar_t__ scnprintf (char*,int,char*) ; 

__attribute__((used)) static int branch_from_str(char *bf, int bfsize,
			   u64 branch_count,
			   u64 cycles_count, u64 iter_count,
			   u64 iter_cycles, u64 from_count)
{
	int printed = 0, i = 0;
	u64 cycles, v = 0;

	cycles = cycles_count / branch_count;
	if (cycles) {
		printed += count_pri64_printf(i++, "cycles",
				cycles,
				bf + printed, bfsize - printed);
	}

	if (iter_count && from_count) {
		v = iter_count / from_count;
		if (v) {
			printed += count_pri64_printf(i++, "iter",
					v, bf + printed, bfsize - printed);

			printed += count_pri64_printf(i++, "avg_cycles",
					iter_cycles / iter_count,
					bf + printed, bfsize - printed);
		}
	}

	if (i)
		printed += scnprintf(bf + printed, bfsize - printed, ")");

	return printed;
}