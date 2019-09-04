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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int sscanf (char*,char*,unsigned long*) ; 

unsigned long default_huge_page_size(void)
{
	unsigned long hps = 0;
	char *line = NULL;
	size_t linelen = 0;
	FILE *f = fopen("/proc/meminfo", "r");

	if (!f)
		return 0;
	while (getline(&line, &linelen, f) > 0) {
		if (sscanf(line, "Hugepagesize:       %lu kB", &hps) == 1) {
			hps <<= 10;
			break;
		}
	}

	free(line);
	fclose(f);
	return hps;
}