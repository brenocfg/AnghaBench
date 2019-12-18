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
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ * seek_to_smaps_entry (unsigned long) ; 
 int sscanf (char*,char*,unsigned long*) ; 
 int /*<<< orphan*/  strstr (char*,char*) ; 

int get_proc_page_size(unsigned long addr)
{
	FILE *smaps;
	char *line;
	unsigned long mmupage_size = 0;
	size_t size;

	smaps = seek_to_smaps_entry(addr);
	if (!smaps) {
		printf("Unable to parse /proc/self/smaps\n");
		return 0;
	}

	while (getline(&line, &size, smaps) > 0) {
		if (!strstr(line, "MMUPageSize")) {
			free(line);
			line = NULL;
			size = 0;
			continue;
		}

		/* found the MMUPageSize of this section */
		if (sscanf(line, "MMUPageSize:    %8lu kB",
					&mmupage_size) < 1) {
			printf("Unable to parse smaps entry for Size:%s\n",
					line);
			break;
		}

	}
	free(line);
	if (smaps)
		fclose(smaps);
	return mmupage_size << 10;
}