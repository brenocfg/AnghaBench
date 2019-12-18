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
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 

__attribute__((used)) static void
usage(const char *progname, int status)
{
	FILE *stream = (status != EXIT_SUCCESS) ? stderr : stdout;
	int i;

	fprintf(stream, "Usage: %s [OPTIONS...]\n", progname);
	fprintf(stream, "\n"
			"Options:\n"
			"  -f <file>		generate a factory flash image <file>\n"
			"  -s <file>		generate a sysupgrade flash image <file>\n"
			"  -h			show this screen\n");
	exit(status);
}