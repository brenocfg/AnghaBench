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
 int /*<<< orphan*/  LOCKED ; 
 int /*<<< orphan*/  RSS ; 
 int /*<<< orphan*/  SIZE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int is_vmflag_set (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ * seek_to_smaps_entry (unsigned long) ; 
 int sscanf (char*,char*,unsigned long*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strstr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_vma_lock_on_fault(unsigned long addr)
{
	bool ret = false;
	bool locked;
	FILE *smaps = NULL;
	unsigned long vma_size, vma_rss;
	char *line = NULL;
	char *value;
	size_t size = 0;

	locked = is_vmflag_set(addr, LOCKED);
	if (!locked)
		goto out;

	smaps = seek_to_smaps_entry(addr);
	if (!smaps) {
		printf("Unable to parse /proc/self/smaps\n");
		goto out;
	}

	while (getline(&line, &size, smaps) > 0) {
		if (!strstr(line, SIZE)) {
			free(line);
			line = NULL;
			size = 0;
			continue;
		}

		value = line + strlen(SIZE);
		if (sscanf(value, "%lu kB", &vma_size) < 1) {
			printf("Unable to parse smaps entry for Size\n");
			goto out;
		}
		break;
	}

	while (getline(&line, &size, smaps) > 0) {
		if (!strstr(line, RSS)) {
			free(line);
			line = NULL;
			size = 0;
			continue;
		}

		value = line + strlen(RSS);
		if (sscanf(value, "%lu kB", &vma_rss) < 1) {
			printf("Unable to parse smaps entry for Rss\n");
			goto out;
		}
		break;
	}

	ret = locked && (vma_rss < vma_size);
out:
	free(line);
	if (smaps)
		fclose(smaps);
	return ret;
}