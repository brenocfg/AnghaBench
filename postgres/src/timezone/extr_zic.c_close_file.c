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
 char* _ (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*,char*,char const*,char*,char const*) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
close_file(FILE *stream, char const *dir, char const *name)
{
	char const *e = (ferror(stream) ? _("I/O error")
					 : fclose(stream) != 0 ? strerror(errno) : NULL);

	if (e)
	{
		fprintf(stderr, "%s: %s%s%s%s%s\n", progname,
				dir ? dir : "", dir ? "/" : "",
				name ? name : "", name ? ": " : "",
				e);
		exit(EXIT_FAILURE);
	}
}