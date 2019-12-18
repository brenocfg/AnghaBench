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
 int /*<<< orphan*/  CLONE_NEWNS ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  KSFT_SKIP ; 
 int MS_PRIVATE ; 
 int MS_REC ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 int mount (char*,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int unshare (int /*<<< orphan*/ ) ; 
 int verify_invalid_ptmx_bind_mount () ; 
 int verify_non_standard_devpts_mount () ; 
 int verify_ptmx_bind_mount () ; 

int main(int argc, char *argv[])
{
	int ret;

	if (!isatty(STDIN_FILENO)) {
		fprintf(stderr, "Standard input file descriptor is not attached "
				"to a terminal. Skipping test\n");
		exit(KSFT_SKIP);
	}

	ret = unshare(CLONE_NEWNS);
	if (ret < 0) {
		fprintf(stderr, "Failed to unshare mount namespace\n");
		exit(EXIT_FAILURE);
	}

	ret = mount("", "/", NULL, MS_PRIVATE | MS_REC, 0);
	if (ret < 0) {
		fprintf(stderr, "Failed to make \"/\" MS_PRIVATE in new mount "
				"namespace\n");
		exit(EXIT_FAILURE);
	}

	ret = verify_ptmx_bind_mount();
	if (ret < 0)
		exit(EXIT_FAILURE);

	ret = verify_invalid_ptmx_bind_mount();
	if (ret < 0)
		exit(EXIT_FAILURE);

	ret = verify_non_standard_devpts_mount();
	if (ret < 0)
		exit(EXIT_FAILURE);

	exit(EXIT_SUCCESS);
}