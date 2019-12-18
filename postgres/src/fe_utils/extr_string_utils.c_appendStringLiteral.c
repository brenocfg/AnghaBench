#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* data; int len; int maxlen; } ;
typedef  TYPE_1__* PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  IS_HIGHBIT_SET (char) ; 
 int PQmblen (char const*,int) ; 
 scalar_t__ SQL_STR_DOUBLE (char,int) ; 
 int /*<<< orphan*/  enlargePQExpBuffer (TYPE_1__*,int) ; 
 size_t strlen (char const*) ; 

void
appendStringLiteral(PQExpBuffer buf, const char *str,
					int encoding, bool std_strings)
{
	size_t		length = strlen(str);
	const char *source = str;
	char	   *target;

	if (!enlargePQExpBuffer(buf, 2 * length + 2))
		return;

	target = buf->data + buf->len;
	*target++ = '\'';

	while (*source != '\0')
	{
		char		c = *source;
		int			len;
		int			i;

		/* Fast path for plain ASCII */
		if (!IS_HIGHBIT_SET(c))
		{
			/* Apply quoting if needed */
			if (SQL_STR_DOUBLE(c, !std_strings))
				*target++ = c;
			/* Copy the character */
			*target++ = c;
			source++;
			continue;
		}

		/* Slow path for possible multibyte characters */
		len = PQmblen(source, encoding);

		/* Copy the character */
		for (i = 0; i < len; i++)
		{
			if (*source == '\0')
				break;
			*target++ = *source++;
		}

		/*
		 * If we hit premature end of string (ie, incomplete multibyte
		 * character), try to pad out to the correct length with spaces. We
		 * may not be able to pad completely, but we will always be able to
		 * insert at least one pad space (since we'd not have quoted a
		 * multibyte character).  This should be enough to make a string that
		 * the server will error out on.
		 */
		if (i < len)
		{
			char	   *stop = buf->data + buf->maxlen - 2;

			for (; i < len; i++)
			{
				if (target >= stop)
					break;
				*target++ = ' ';
			}
			break;
		}
	}

	/* Write the terminating quote and NUL character. */
	*target++ = '\'';
	*target = '\0';

	buf->len = target - buf->data;
}