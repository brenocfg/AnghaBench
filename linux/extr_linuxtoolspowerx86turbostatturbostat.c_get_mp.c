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
struct msr_counter {scalar_t__ msr_num; int flags; char* path; } ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_BYTES ; 
 int SYSFS_PERCPU ; 
 scalar_t__ get_msr (int,scalar_t__,unsigned long long*) ; 
 unsigned long long snapshot_sysfs_counter (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,char*) ; 

int get_mp(int cpu, struct msr_counter *mp, unsigned long long *counterp)
{
	if (mp->msr_num != 0) {
		if (get_msr(cpu, mp->msr_num, counterp))
			return -1;
	} else {
		char path[128 + PATH_BYTES];

		if (mp->flags & SYSFS_PERCPU) {
			sprintf(path, "/sys/devices/system/cpu/cpu%d/%s",
				 cpu, mp->path);

			*counterp = snapshot_sysfs_counter(path);
		} else {
			*counterp = snapshot_sysfs_counter(mp->path);
		}
	}

	return 0;
}