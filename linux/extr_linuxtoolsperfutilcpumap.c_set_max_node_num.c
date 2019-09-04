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
 int max_node_num ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int snprintf (char*,int,char*,char const*) ; 
 char* sysfs__mountpoint () ; 

__attribute__((used)) static void set_max_node_num(void)
{
	const char *mnt;
	char path[PATH_MAX];
	int ret = -1;

	/* set up default */
	max_node_num = 8;

	mnt = sysfs__mountpoint();
	if (!mnt)
		goto out;

	/* get the highest possible cpu number for a sparse allocation */
	ret = snprintf(path, PATH_MAX, "%s/devices/system/node/possible", mnt);
	if (ret == PATH_MAX) {
		pr_err("sysfs path crossed PATH_MAX(%d) size\n", PATH_MAX);
		goto out;
	}

	ret = get_max_num(path, &max_node_num);

out:
	if (ret)
		pr_err("Failed to read max nodes, using default of %d\n", max_node_num);
}