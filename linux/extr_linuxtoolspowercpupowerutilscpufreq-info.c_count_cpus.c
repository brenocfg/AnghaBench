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
 int LINE_LEN ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int sscanf (char*,char*,unsigned int*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static unsigned int count_cpus(void)
{
	FILE *fp;
	char value[LINE_LEN];
	unsigned int ret = 0;
	unsigned int cpunr = 0;

	fp = fopen("/proc/stat", "r");
	if (!fp) {
		printf(_("Couldn't count the number of CPUs (%s: %s), assuming 1\n"), "/proc/stat", strerror(errno));
		return 1;
	}

	while (!feof(fp)) {
		if (!fgets(value, LINE_LEN, fp))
			continue;
		value[LINE_LEN - 1] = '\0';
		if (strlen(value) < (LINE_LEN - 2))
			continue;
		if (strstr(value, "cpu "))
			continue;
		if (sscanf(value, "cpu%d ", &cpunr) != 1)
			continue;
		if (cpunr > ret)
			ret = cpunr;
	}
	fclose(fp);

	/* cpu count starts from 0, on error return 1 (UP) */
	return ret + 1;
}