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
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ pg_malloc (int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char const*) ; 
 char* strstr (char*,char const*) ; 

__attribute__((used)) static char **
replace_token(char **lines, const char *token, const char *replacement)
{
	int			numlines = 1;
	int			i;
	char	  **result;
	int			toklen,
				replen,
				diff;

	for (i = 0; lines[i]; i++)
		numlines++;

	result = (char **) pg_malloc(numlines * sizeof(char *));

	toklen = strlen(token);
	replen = strlen(replacement);
	diff = replen - toklen;

	for (i = 0; i < numlines; i++)
	{
		char	   *where;
		char	   *newline;
		int			pre;

		/* just copy pointer if NULL or no change needed */
		if (lines[i] == NULL || (where = strstr(lines[i], token)) == NULL)
		{
			result[i] = lines[i];
			continue;
		}

		/* if we get here a change is needed - set up new line */

		newline = (char *) pg_malloc(strlen(lines[i]) + diff + 1);

		pre = where - lines[i];

		memcpy(newline, lines[i], pre);

		memcpy(newline + pre, replacement, replen);

		strcpy(newline + pre + replen, lines[i] + pre + toklen);

		result[i] = newline;
	}

	return result;
}