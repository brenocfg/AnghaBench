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
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,size_t*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

ssize_t get_base_addr() {
	size_t start;
	char buf[256];
	FILE *f;

	f = fopen("/proc/self/maps", "r");
	if (!f)
		return -errno;

	while (fscanf(f, "%zx-%*x %s %*s\n", &start, buf) == 2) {
		if (strcmp(buf, "r-xp") == 0) {
			fclose(f);
			return start;
		}
	}

	fclose(f);
	return -EINVAL;
}