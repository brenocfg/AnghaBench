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
typedef  int /*<<< orphan*/  desc ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BIC_sysfs ; 
 int /*<<< orphan*/  DO_BIC (int /*<<< orphan*/ ) ; 
 int base_cpu ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*,char*) ; 
 int /*<<< orphan*/  outf ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 char* strchr (char*,char) ; 
 char* strchrnul (char*,char) ; 

__attribute__((used)) static void
dump_sysfs_cstate_config(void)
{
	char path[64];
	char name_buf[16];
	char desc[64];
	FILE *input;
	int state;
	char *sp;

	if (!DO_BIC(BIC_sysfs))
		return;

	for (state = 0; state < 10; ++state) {

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

		sprintf(path, "/sys/devices/system/cpu/cpu%d/cpuidle/state%d/desc",
			base_cpu, state);
		input = fopen(path, "r");
		if (input == NULL)
			continue;
		if (!fgets(desc, sizeof(desc), input))
			err(1, "%s: failed to read file", path);

		fprintf(outf, "cpu%d: %s: %s", base_cpu, name_buf, desc);
		fclose(input);
	}
}