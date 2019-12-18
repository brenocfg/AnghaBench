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
 int EOF ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pg_log_error (char*,char const*) ; 
 scalar_t__ pg_malloc (int) ; 
 char* pg_strdup (char*) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char **
readfile(const char *path)
{
	FILE	   *infile;
	int			maxlength = 1,
				linelen = 0;
	int			nlines = 0;
	int			n;
	char	  **result;
	char	   *buffer;
	int			c;

	if ((infile = fopen(path, "r")) == NULL)
	{
		pg_log_error("could not open file \"%s\" for reading: %m", path);
		exit(1);
	}

	/* pass over the file twice - the first time to size the result */

	while ((c = fgetc(infile)) != EOF)
	{
		linelen++;
		if (c == '\n')
		{
			nlines++;
			if (linelen > maxlength)
				maxlength = linelen;
			linelen = 0;
		}
	}

	/* handle last line without a terminating newline (yuck) */
	if (linelen)
		nlines++;
	if (linelen > maxlength)
		maxlength = linelen;

	/* set up the result and the line buffer */
	result = (char **) pg_malloc((nlines + 1) * sizeof(char *));
	buffer = (char *) pg_malloc(maxlength + 1);

	/* now reprocess the file and store the lines */
	rewind(infile);
	n = 0;
	while (fgets(buffer, maxlength + 1, infile) != NULL && n < nlines)
		result[n++] = pg_strdup(buffer);

	fclose(infile);
	free(buffer);
	result[n] = NULL;

	return result;
}