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
 int /*<<< orphan*/  scnprintf (char*,int,char*,char const*,char const*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* sysfs__mountpoint () ; 

__attribute__((used)) static int is_arm_pmu_core(const char *name)
{
	struct stat st;
	char path[PATH_MAX];
	const char *sysfs = sysfs__mountpoint();

	if (!sysfs)
		return 0;

	/* Look for cpu sysfs (specific to arm) */
	scnprintf(path, PATH_MAX, "%s/bus/event_source/devices/%s/cpus",
				sysfs, name);
	if (stat(path, &st) == 0)
		return 1;

	return 0;
}