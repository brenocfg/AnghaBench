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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,size_t) ; 

__attribute__((used)) static void
print_with_linenumbers(FILE *output, char *lines,
					   const char *header_keyword)
{
	bool		in_header = (header_keyword != NULL);
	size_t		header_sz = in_header ? strlen(header_keyword) : 0;
	int			lineno = 0;

	while (*lines != '\0')
	{
		char	   *eol;

		if (in_header && strncmp(lines, header_keyword, header_sz) == 0)
			in_header = false;

		/* increment lineno only for body's lines */
		if (!in_header)
			lineno++;

		/* find and mark end of current line */
		eol = strchr(lines, '\n');
		if (eol != NULL)
			*eol = '\0';

		/* show current line as appropriate */
		if (in_header)
			fprintf(output, "        %s\n", lines);
		else
			fprintf(output, "%-7d %s\n", lineno, lines);

		/* advance to next line, if any */
		if (eol == NULL)
			break;
		lines = ++eol;
	}
}