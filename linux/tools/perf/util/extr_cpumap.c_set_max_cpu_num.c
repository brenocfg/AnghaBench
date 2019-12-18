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
 int PATH_MAX ; 
 int get_max_num (char*,int*) ; 
 int max_cpu_num ; 
 int max_present_cpu_num ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int snprintf (char*,int,char*,char const*) ; 
 char* sysfs__mountpoint () ; 

__attribute__((used)) static void set_max_cpu_num(void)
{
	const char *mnt;
	char path[PATH_MAX];
	int ret = -1;

	/* set up default */
	max_cpu_num = 4096;
	max_present_cpu_num = 4096;

	mnt = sysfs__mountpoint();
	if (!mnt)
		goto out;

	/* get the highest possible cpu number for a sparse allocation */
	ret = snprintf(path, PATH_MAX, "%s/devices/system/cpu/possible", mnt);
	if (ret == PATH_MAX) {
		pr_err("sysfs path crossed PATH_MAX(%d) size\n", PATH_MAX);
		goto out;
	}

	ret = get_max_num(path, &max_cpu_num);
	if (ret)
		goto out;

	/* get the highest present cpu number for a sparse allocation */
	ret = snprintf(path, PATH_MAX, "%s/devices/system/cpu/present", mnt);
	if (ret == PATH_MAX) {
		pr_err("sysfs path crossed PATH_MAX(%d) size\n", PATH_MAX);
		goto out;
	}

	ret = get_max_num(path, &max_present_cpu_num);

out:
	if (ret)
		pr_err("Failed to read max cpus, using default of %d\n", max_cpu_num);
}