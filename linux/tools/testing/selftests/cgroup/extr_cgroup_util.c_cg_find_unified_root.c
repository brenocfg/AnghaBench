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
 scalar_t__ read_text (char*,char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 
 char* strtok (char*,char const*) ; 

int cg_find_unified_root(char *root, size_t len)
{
	char buf[10 * PAGE_SIZE];
	char *fs, *mount, *type;
	const char delim[] = "\n\t ";

	if (read_text("/proc/self/mounts", buf, sizeof(buf)) <= 0)
		return -1;

	/*
	 * Example:
	 * cgroup /sys/fs/cgroup cgroup2 rw,seclabel,noexec,relatime 0 0
	 */
	for (fs = strtok(buf, delim); fs; fs = strtok(NULL, delim)) {
		mount = strtok(NULL, delim);
		type = strtok(NULL, delim);
		strtok(NULL, delim);
		strtok(NULL, delim);
		strtok(NULL, delim);

		if (strcmp(type, "cgroup2") == 0) {
			strncpy(root, mount, len);
			return 0;
		}
	}

	return -1;
}