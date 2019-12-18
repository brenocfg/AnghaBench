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
typedef  int /*<<< orphan*/  PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_hexdigit (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static char *
conninfo_uri_decode(const char *str, PQExpBuffer errorMessage)
{
	char	   *buf;
	char	   *p;
	const char *q = str;

	buf = malloc(strlen(str) + 1);
	if (buf == NULL)
	{
		printfPQExpBuffer(errorMessage, libpq_gettext("out of memory\n"));
		return NULL;
	}
	p = buf;

	for (;;)
	{
		if (*q != '%')
		{
			/* copy and check for NUL terminator */
			if (!(*(p++) = *(q++)))
				break;
		}
		else
		{
			int			hi;
			int			lo;
			int			c;

			++q;				/* skip the percent sign itself */

			/*
			 * Possible EOL will be caught by the first call to
			 * get_hexdigit(), so we never dereference an invalid q pointer.
			 */
			if (!(get_hexdigit(*q++, &hi) && get_hexdigit(*q++, &lo)))
			{
				printfPQExpBuffer(errorMessage,
								  libpq_gettext("invalid percent-encoded token: \"%s\"\n"),
								  str);
				free(buf);
				return NULL;
			}

			c = (hi << 4) | lo;
			if (c == 0)
			{
				printfPQExpBuffer(errorMessage,
								  libpq_gettext("forbidden value %%00 in percent-encoded value: \"%s\"\n"),
								  str);
				free(buf);
				return NULL;
			}
			*(p++) = c;
		}
	}

	return buf;
}