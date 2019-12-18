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
 int /*<<< orphan*/  Assert (int) ; 
 int PQmblen (char const*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* pg_malloc (int) ; 
 scalar_t__ strchr (char const*,char) ; 
 int strlen (char const*) ; 

char *
quote_if_needed(const char *source, const char *entails_quote,
				char quote, char escape, int encoding)
{
	const char *src;
	char	   *ret;
	char	   *dst;
	bool		need_quotes = false;

	Assert(source != NULL);
	Assert(quote != '\0');

	src = source;
	dst = ret = pg_malloc(2 * strlen(src) + 3); /* excess */

	*dst++ = quote;

	while (*src)
	{
		char		c = *src;
		int			i;

		if (c == quote)
		{
			need_quotes = true;
			*dst++ = quote;
		}
		else if (c == escape)
		{
			need_quotes = true;
			*dst++ = escape;
		}
		else if (strchr(entails_quote, c))
			need_quotes = true;

		i = PQmblen(src, encoding);
		while (i--)
			*dst++ = *src++;
	}

	*dst++ = quote;
	*dst = '\0';

	if (!need_quotes)
	{
		free(ret);
		ret = NULL;
	}

	return ret;
}