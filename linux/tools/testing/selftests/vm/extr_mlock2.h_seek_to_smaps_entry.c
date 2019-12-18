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
 int BUFSIZ ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int sscanf (char*,char*,unsigned long*,unsigned long*,char*,unsigned long*,char*,unsigned long*,char*) ; 

__attribute__((used)) static FILE *seek_to_smaps_entry(unsigned long addr)
{
	FILE *file;
	char *line = NULL;
	size_t size = 0;
	unsigned long start, end;
	char perms[5];
	unsigned long offset;
	char dev[32];
	unsigned long inode;
	char path[BUFSIZ];

	file = fopen("/proc/self/smaps", "r");
	if (!file) {
		perror("fopen smaps");
		_exit(1);
	}

	while (getline(&line, &size, file) > 0) {
		if (sscanf(line, "%lx-%lx %s %lx %s %lu %s\n",
			   &start, &end, perms, &offset, dev, &inode, path) < 6)
			goto next;

		if (start <= addr && addr < end)
			goto out;

next:
		free(line);
		line = NULL;
		size = 0;
	}

	fclose(file);
	file = NULL;

out:
	free(line);
	return file;
}