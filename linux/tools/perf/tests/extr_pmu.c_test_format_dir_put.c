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
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int system (char*) ; 

__attribute__((used)) static int test_format_dir_put(char *dir)
{
	char buf[PATH_MAX];
	snprintf(buf, PATH_MAX, "rm -f %s/*\n", dir);
	if (system(buf))
		return -1;

	snprintf(buf, PATH_MAX, "rmdir %s\n", dir);
	return system(buf);
}