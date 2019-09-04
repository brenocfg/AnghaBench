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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ write_text (char*,char*,scalar_t__) ; 

int cg_write(const char *cgroup, const char *control, char *buf)
{
	char path[PATH_MAX];
	ssize_t len = strlen(buf);

	snprintf(path, sizeof(path), "%s/%s", cgroup, control);

	if (write_text(path, buf, len) == len)
		return 0;

	return -1;
}