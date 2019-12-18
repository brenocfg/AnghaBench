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
#define  SJ_FAIL 130 
#define  SJ_SETJMP 129 
#define  SJ_SUCCEED 128 
 int /*<<< orphan*/  do_file (char*) ; 
 int /*<<< orphan*/ * ehdr_curr ; 
 int /*<<< orphan*/  exit (int) ; 
 int fd_map ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  jmpenv ; 
 int mmap_failed ; 
 int setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int
main(int argc, char *argv[])
{
	int n_error = 0;  /* gcc-4.3.0 false positive complaint */
	int i;

	if (argc < 2) {
		fprintf(stderr, "usage: sortextable vmlinux...\n");
		return 0;
	}

	/* Process each file in turn, allowing deep failure. */
	for (i = 1; i < argc; i++) {
		char *file = argv[i];
		int const sjval = setjmp(jmpenv);

		switch (sjval) {
		default:
			fprintf(stderr, "internal error: %s\n", file);
			exit(1);
			break;
		case SJ_SETJMP:    /* normal sequence */
			/* Avoid problems if early cleanup() */
			fd_map = -1;
			ehdr_curr = NULL;
			mmap_failed = 1;
			do_file(file);
			break;
		case SJ_FAIL:    /* error in do_file or below */
			++n_error;
			break;
		case SJ_SUCCEED:    /* premature success */
			/* do nothing */
			break;
		}  /* end switch */
	}
	return !!n_error;
}