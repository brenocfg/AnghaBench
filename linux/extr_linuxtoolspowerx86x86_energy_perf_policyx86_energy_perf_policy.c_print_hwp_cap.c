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
struct msr_hwp_cap {int lowest; int efficient; int guaranteed; int highest; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,...) ; 

void print_hwp_cap(int cpu, struct msr_hwp_cap *cap, char *str)
{
	if (cpu != -1)
		printf("cpu%d: ", cpu);

	printf("HWP_CAP: low %d eff %d guar %d high %d\n",
		cap->lowest, cap->efficient, cap->guaranteed, cap->highest);
}