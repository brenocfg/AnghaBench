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

/* Variables and functions */
 unsigned int AMD_FAM14H_STATE_NUM ; 
 unsigned long** current_count ; 
 int /*<<< orphan*/  dprint (char*,double,unsigned long,double) ; 
 unsigned long** previous_count ; 
 double timediff ; 

__attribute__((used)) static int fam14h_get_count_percent(unsigned int id, double *percent,
				    unsigned int cpu)
{
	unsigned long diff;

	if (id >= AMD_FAM14H_STATE_NUM)
		return -1;
	/* residency count in 80ns -> divide through 12.5 to get us residency */
	diff = current_count[id][cpu] - previous_count[id][cpu];

	if (timediff == 0)
		*percent = 0.0;
	else
		*percent = 100.0 * diff / timediff / 12.5;

	dprint("Timediff: %llu - res~: %lu us - percent: %.2f %%\n",
	       timediff, diff * 10 / 125, *percent);

	return 0;
}