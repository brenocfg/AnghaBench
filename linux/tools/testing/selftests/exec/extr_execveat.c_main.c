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

/* Variables and functions */
 int atoi (char*) ; 
 char** envp ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  prerequisites () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int run_tests () ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char const*,char*) ; 

int main(int argc, char **argv)
{
	int ii;
	int rc;
	const char *verbose = getenv("VERBOSE");

	if (argc >= 2) {
		/* If we are invoked with an argument, don't run tests. */
		const char *in_test = getenv("IN_TEST");

		if (verbose) {
			printf("  invoked with:");
			for (ii = 0; ii < argc; ii++)
				printf(" [%d]='%s'", ii, argv[ii]);
			printf("\n");
		}

		/* Check expected environment transferred. */
		if (!in_test || strcmp(in_test, "yes") != 0) {
			printf("[FAIL] (no IN_TEST=yes in env)\n");
			return 1;
		}

		/* Use the final argument as an exit code. */
		rc = atoi(argv[argc - 1]);
		fflush(stdout);
	} else {
		prerequisites();
		if (verbose)
			envp[1] = "VERBOSE=1";
		rc = run_tests();
		if (rc > 0)
			printf("%d tests failed\n", rc);
	}
	return rc;
}