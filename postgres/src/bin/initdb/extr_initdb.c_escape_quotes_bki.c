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
 char* escape_quotes (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ pg_malloc (scalar_t__) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static char *
escape_quotes_bki(const char *src)
{
	char	   *result;
	char	   *data = escape_quotes(src);
	char	   *resultp;
	char	   *datap;
	int			nquotes = 0;

	/* count double quotes in data */
	datap = data;
	while ((datap = strchr(datap, '"')) != NULL)
	{
		nquotes++;
		datap++;
	}

	result = (char *) pg_malloc(strlen(data) + 3 + nquotes * 3);
	resultp = result;
	*resultp++ = '"';
	for (datap = data; *datap; datap++)
	{
		if (*datap == '"')
		{
			strcpy(resultp, "\\042");
			resultp += 4;
		}
		else
			*resultp++ = *datap;
	}
	*resultp++ = '"';
	*resultp = '\0';

	free(data);
	return result;
}