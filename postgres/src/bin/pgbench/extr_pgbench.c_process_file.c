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
 int /*<<< orphan*/  ParseScript (char*,char const*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* read_file_contents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_file(const char *filename, int weight)
{
	FILE	   *fd;
	char	   *buf;

	/* Slurp the file contents into "buf" */
	if (strcmp(filename, "-") == 0)
		fd = stdin;
	else if ((fd = fopen(filename, "r")) == NULL)
	{
		fprintf(stderr, "could not open file \"%s\": %s\n",
				filename, strerror(errno));
		exit(1);
	}

	buf = read_file_contents(fd);

	if (ferror(fd))
	{
		fprintf(stderr, "could not read file \"%s\": %s\n",
				filename, strerror(errno));
		exit(1);
	}

	if (fd != stdin)
		fclose(fd);

	ParseScript(buf, filename, weight);

	free(buf);
}