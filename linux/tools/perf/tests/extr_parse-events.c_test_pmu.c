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
struct stat {int dummy; } ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int stat (char*,struct stat*) ; 
 char* sysfs__mountpoint () ; 

__attribute__((used)) static int test_pmu(void)
{
	struct stat st;
	char path[PATH_MAX];
	int ret;

	snprintf(path, PATH_MAX, "%s/bus/event_source/devices/cpu/format/",
		 sysfs__mountpoint());

	ret = stat(path, &st);
	if (ret)
		pr_debug("omitting PMU cpu tests\n");
	return !ret;
}