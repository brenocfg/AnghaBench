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
typedef  int /*<<< orphan*/  name_buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BIC_sysfs ; 
 int /*<<< orphan*/  COUNTER_ITEMS ; 
 int /*<<< orphan*/  COUNTER_USEC ; 
 int /*<<< orphan*/  DO_BIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FORMAT_DELTA ; 
 int /*<<< orphan*/  FORMAT_PERCENT ; 
 int /*<<< orphan*/  SCOPE_CPU ; 
 int /*<<< orphan*/  SYSFS_PERCPU ; 
 int /*<<< orphan*/  add_counter (int /*<<< orphan*/ ,char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int base_cpu ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ is_deferred_skip (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 
 char* strchr (char*,char) ; 
 char* strchrnul (char*,char) ; 

void probe_sysfs(void)
{
	char path[64];
	char name_buf[16];
	FILE *input;
	int state;
	char *sp;

	if (!DO_BIC(BIC_sysfs))
		return;

	for (state = 10; state >= 0; --state) {

		sprintf(path, "/sys/devices/system/cpu/cpu%d/cpuidle/state%d/name",
			base_cpu, state);
		input = fopen(path, "r");
		if (input == NULL)
			continue;
		if (!fgets(name_buf, sizeof(name_buf), input))
			err(1, "%s: failed to read file", path);

		 /* truncate "C1-HSW\n" to "C1", or truncate "C1\n" to "C1" */
		sp = strchr(name_buf, '-');
		if (!sp)
			sp = strchrnul(name_buf, '\n');
		*sp = '%';
		*(sp + 1) = '\0';

		fclose(input);

		sprintf(path, "cpuidle/state%d/time", state);

		if (is_deferred_skip(name_buf))
			continue;

		add_counter(0, path, name_buf, 64, SCOPE_CPU, COUNTER_USEC,
				FORMAT_PERCENT, SYSFS_PERCPU);
	}

	for (state = 10; state >= 0; --state) {

		sprintf(path, "/sys/devices/system/cpu/cpu%d/cpuidle/state%d/name",
			base_cpu, state);
		input = fopen(path, "r");
		if (input == NULL)
			continue;
		if (!fgets(name_buf, sizeof(name_buf), input))
			err(1, "%s: failed to read file", path);
		 /* truncate "C1-HSW\n" to "C1", or truncate "C1\n" to "C1" */
		sp = strchr(name_buf, '-');
		if (!sp)
			sp = strchrnul(name_buf, '\n');
		*sp = '\0';
		fclose(input);

		sprintf(path, "cpuidle/state%d/usage", state);

		if (is_deferred_skip(name_buf))
			continue;

		add_counter(0, path, name_buf, 64, SCOPE_CPU, COUNTER_ITEMS,
				FORMAT_DELTA, SYSFS_PERCPU);
	}

}