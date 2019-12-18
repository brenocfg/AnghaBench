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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen_or_die (char*,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,unsigned long long*) ; 

unsigned long long snapshot_sysfs_counter(char *path)
{
	FILE *fp;
	int retval;
	unsigned long long counter;

	fp = fopen_or_die(path, "r");

	retval = fscanf(fp, "%lld", &counter);
	if (retval != 1)
		err(1, "snapshot_sysfs_counter(%s)", path);

	fclose(fp);

	return counter;
}