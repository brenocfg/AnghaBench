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
 int /*<<< orphan*/  PATH_MAX ; 
 int TEST_FAIL ; 
 int TEST_PASS ; 
 int /*<<< orphan*/  core_pattern_file ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int fread (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int write_core_pattern (char*) ; 

__attribute__((used)) static int setup_core_pattern(char **core_pattern_, bool *changed_)
{
	FILE *f;
	char *core_pattern;
	int ret;

	core_pattern = malloc(PATH_MAX);
	if (!core_pattern) {
		perror("Error allocating memory");
		return TEST_FAIL;
	}

	f = fopen(core_pattern_file, "r");
	if (!f) {
		perror("Error opening core_pattern file");
		ret = TEST_FAIL;
		goto out;
	}

	ret = fread(core_pattern, 1, PATH_MAX, f);
	fclose(f);
	if (!ret) {
		perror("Error reading core_pattern file");
		ret = TEST_FAIL;
		goto out;
	}

	/* Check whether we can predict the name of the core file. */
	if (!strcmp(core_pattern, "core") || !strcmp(core_pattern, "core.%p"))
		*changed_ = false;
	else {
		ret = write_core_pattern("core-pkey.%p");
		if (ret)
			goto out;

		*changed_ = true;
	}

	*core_pattern_ = core_pattern;
	ret = TEST_PASS;

 out:
	if (ret)
		free(core_pattern);

	return ret;
}