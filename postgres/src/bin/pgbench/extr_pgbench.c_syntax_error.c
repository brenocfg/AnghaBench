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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

void
syntax_error(const char *source, int lineno,
			 const char *line, const char *command,
			 const char *msg, const char *more, int column)
{
	fprintf(stderr, "%s:%d: %s", source, lineno, msg);
	if (more != NULL)
		fprintf(stderr, " (%s)", more);
	if (column >= 0 && line == NULL)
		fprintf(stderr, " at column %d", column + 1);
	if (command != NULL)
		fprintf(stderr, " in command \"%s\"", command);
	fprintf(stderr, "\n");
	if (line != NULL)
	{
		fprintf(stderr, "%s\n", line);
		if (column >= 0)
		{
			int			i;

			for (i = 0; i < column; i++)
				fprintf(stderr, " ");
			fprintf(stderr, "^ error found here\n");
		}
	}
	exit(1);
}