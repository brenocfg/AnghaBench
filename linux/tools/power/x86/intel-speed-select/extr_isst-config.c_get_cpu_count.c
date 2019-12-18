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
 int MAX_DIE_PER_PACKAGE ; 
 int MAX_PACKAGE_COUNT ; 
 int** cpu_cnt ; 

int get_cpu_count(int pkg_id, int die_id)
{
	if (pkg_id < MAX_PACKAGE_COUNT && die_id < MAX_DIE_PER_PACKAGE)
		return cpu_cnt[pkg_id][die_id];

	return 0;
}