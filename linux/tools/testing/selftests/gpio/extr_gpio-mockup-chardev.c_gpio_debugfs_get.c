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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int IN ; 
 int OUT ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_debugfs (char**) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 char* strstr (char*,char const*) ; 

__attribute__((used)) static int gpio_debugfs_get(const char *consumer, int *dir, int *value)
{
	char *debugfs;
	FILE *f;
	char *line = NULL;
	size_t len = 0;
	char *cur;
	int found = 0;

	if (get_debugfs(&debugfs) != 0)
		err(EXIT_FAILURE, "debugfs is not mounted");

	f = fopen(debugfs, "r");
	if (!f)
		err(EXIT_FAILURE, "read from gpio debugfs failed");

	/*
	 * gpio-2   (                    |gpio-selftest               ) in  lo
	 */
	while (getline(&line, &len, f) != -1) {
		cur = strstr(line, consumer);
		if (cur == NULL)
			continue;

		cur = strchr(line, ')');
		if (!cur)
			continue;

		cur += 2;
		if (!strncmp(cur, "out", 3)) {
			*dir = OUT;
			cur += 4;
		} else if (!strncmp(cur, "in", 2)) {
			*dir = IN;
			cur += 4;
		}

		if (!strncmp(cur, "hi", 2))
			*value = 1;
		else if (!strncmp(cur, "lo", 2))
			*value = 0;

		found = 1;
		break;
	}
	free(debugfs);
	fclose(f);
	free(line);

	if (!found)
		return -1;

	return 0;
}