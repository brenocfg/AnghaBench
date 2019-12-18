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
typedef  int /*<<< orphan*/  ftrace ;

/* Variables and functions */
 scalar_t__ do_file (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char*) ; 
 int optind ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int strlen (char*) ; 
 int warn_on_notrace_sect ; 

int main(int argc, char *argv[])
{
	const char ftrace[] = "/ftrace.o";
	int ftrace_size = sizeof(ftrace) - 1;
	int n_error = 0;  /* gcc-4.3.0 false positive complaint */
	int c;
	int i;

	while ((c = getopt(argc, argv, "w")) >= 0) {
		switch (c) {
		case 'w':
			warn_on_notrace_sect = 1;
			break;
		default:
			fprintf(stderr, "usage: recordmcount [-w] file.o...\n");
			return 0;
		}
	}

	if ((argc - optind) < 1) {
		fprintf(stderr, "usage: recordmcount [-w] file.o...\n");
		return 0;
	}

	/* Process each file in turn, allowing deep failure. */
	for (i = optind; i < argc; i++) {
		char *file = argv[i];
		int len;

		/*
		 * The file kernel/trace/ftrace.o references the mcount
		 * function but does not call it. Since ftrace.o should
		 * not be traced anyway, we just skip it.
		 */
		len = strlen(file);
		if (len >= ftrace_size &&
		    strcmp(file + (len - ftrace_size), ftrace) == 0)
			continue;

		if (do_file(file)) {
			fprintf(stderr, "%s: failed\n", file);
			++n_error;
		}
	}
	return !!n_error;
}