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
 char const* VMFLAGS ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ * seek_to_smaps_entry (unsigned long) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/ * strstr (char*,char const*) ; 

__attribute__((used)) static bool is_vmflag_set(unsigned long addr, const char *vmflag)
{
	char *line = NULL;
	char *flags;
	size_t size = 0;
	bool ret = false;
	FILE *smaps;

	smaps = seek_to_smaps_entry(addr);
	if (!smaps) {
		printf("Unable to parse /proc/self/smaps\n");
		goto out;
	}

	while (getline(&line, &size, smaps) > 0) {
		if (!strstr(line, VMFLAGS)) {
			free(line);
			line = NULL;
			size = 0;
			continue;
		}

		flags = line + strlen(VMFLAGS);
		ret = (strstr(flags, vmflag) != NULL);
		goto out;
	}

out:
	free(line);
	fclose(smaps);
	return ret;
}