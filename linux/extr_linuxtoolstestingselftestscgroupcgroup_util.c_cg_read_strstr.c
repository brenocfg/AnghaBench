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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int PAGE_SIZE ; 
 scalar_t__ cg_read (char const*,char const*,char*,int) ; 
 scalar_t__ strstr (char*,char const*) ; 

int cg_read_strstr(const char *cgroup, const char *control, const char *needle)
{
	char buf[PAGE_SIZE];

	if (cg_read(cgroup, control, buf, sizeof(buf)))
		return -1;

	return strstr(buf, needle) ? 0 : -1;
}