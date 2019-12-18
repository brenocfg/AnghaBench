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
 char* _ (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int fclose (int /*<<< orphan*/ ) ; 
 int ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (int /*<<< orphan*/ ) ; 

extern void
tuklib_exit(int status, int err_status, int show_error)
{
	if (status != err_status) {
		// Close stdout. If something goes wrong,
		// print an error message to stderr.
		const int ferror_err = ferror(stdout);
		const int fclose_err = fclose(stdout);
		if (ferror_err || fclose_err) {
			status = err_status;

			// If it was fclose() that failed, we have the reason
			// in errno. If only ferror() indicated an error,
			// we have no idea what the reason was.
			if (show_error)
				fprintf(stderr, "%s: %s: %s\n", progname,
						_("Writing to standard "
							"output failed"),
						fclose_err ? strerror(errno)
							: _("Unknown error"));
		}
	}

	if (status != err_status) {
		// Close stderr. If something goes wrong, there's
		// nothing where we could print an error message.
		// Just set the exit status.
		const int ferror_err = ferror(stderr);
		const int fclose_err = fclose(stderr);
		if (fclose_err || ferror_err)
			status = err_status;
	}

	exit(status);
}