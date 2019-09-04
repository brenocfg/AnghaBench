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
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int PATH_MAX ; 
 scalar_t__ read_text (char*,char*,size_t) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 

int cg_read(const char *cgroup, const char *control, char *buf, size_t len)
{
	char path[PATH_MAX];

	snprintf(path, sizeof(path), "%s/%s", cgroup, control);

	if (read_text(path, buf, len) >= 0)
		return 0;

	return -1;
}