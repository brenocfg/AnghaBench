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
 int LINEBUFSIZE ; 
 int /*<<< orphan*/  StrNCpy (char*,char*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  replace_string (char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static void
ecpg_filter(const char *sourcefile, const char *outfile)
{
	/*
	 * Create a filtered copy of sourcefile, replacing #line x
	 * "./../bla/foo.h" with #line x "foo.h"
	 */
	FILE	   *s,
			   *t;
	char		linebuf[LINEBUFSIZE];

	s = fopen(sourcefile, "r");
	if (!s)
	{
		fprintf(stderr, "Could not open file %s for reading\n", sourcefile);
		exit(2);
	}
	t = fopen(outfile, "w");
	if (!t)
	{
		fprintf(stderr, "Could not open file %s for writing\n", outfile);
		exit(2);
	}

	while (fgets(linebuf, LINEBUFSIZE, s))
	{
		/* check for "#line " in the beginning */
		if (strstr(linebuf, "#line ") == linebuf)
		{
			char	   *p = strchr(linebuf, '"');
			char	   *n;
			int			plen = 1;

			while (*p && (*(p + plen) == '.' || strchr(p + plen, '/') != NULL))
			{
				plen++;
			}
			/* plen is one more than the number of . and / characters */
			if (plen > 1)
			{
				n = (char *) malloc(plen);
				StrNCpy(n, p + 1, plen);
				replace_string(linebuf, n, "");
			}
		}
		fputs(linebuf, t);
	}
	fclose(s);
	fclose(t);
}