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
typedef  int /*<<< orphan*/  disable ;

/* Variables and functions */
 size_t IDLESTATE_DISABLE ; 
 int SYSFS_PATH_MAX ; 
 unsigned int cpuidle_state_count (unsigned int) ; 
 int /*<<< orphan*/  cpuidle_state_file_exists (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int cpuidle_state_write_file (unsigned int,unsigned int,char*,char*,int) ; 
 int /*<<< orphan*/ * idlestate_value_files ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

int cpuidle_state_disable(unsigned int cpu,
			    unsigned int idlestate,
			    unsigned int disable)
{
	char value[SYSFS_PATH_MAX];
	int bytes_written;

	if (cpuidle_state_count(cpu) <= idlestate)
		return -1;

	if (!cpuidle_state_file_exists(cpu, idlestate,
				 idlestate_value_files[IDLESTATE_DISABLE]))
		return -2;

	snprintf(value, SYSFS_PATH_MAX, "%u", disable);

	bytes_written = cpuidle_state_write_file(cpu, idlestate, "disable",
						   value, sizeof(disable));
	if (bytes_written)
		return 0;
	return -3;
}