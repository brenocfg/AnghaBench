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
 int /*<<< orphan*/  ERRCODE_CONFIG_FILE_ERROR ; 
 int /*<<< orphan*/  ereport (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 scalar_t__ pg_isblank (int) ; 

__attribute__((used)) static bool
next_token(char **lineptr, char *buf, int bufsz,
		   bool *initial_quote, bool *terminating_comma,
		   int elevel, char **err_msg)
{
	int			c;
	char	   *start_buf = buf;
	char	   *end_buf = buf + (bufsz - 1);
	bool		in_quote = false;
	bool		was_quote = false;
	bool		saw_quote = false;

	Assert(end_buf > start_buf);

	*initial_quote = false;
	*terminating_comma = false;

	/* Move over any whitespace and commas preceding the next token */
	while ((c = (*(*lineptr)++)) != '\0' && (pg_isblank(c) || c == ','))
		;

	/*
	 * Build a token in buf of next characters up to EOL, unquoted comma, or
	 * unquoted whitespace.
	 */
	while (c != '\0' &&
		   (!pg_isblank(c) || in_quote))
	{
		/* skip comments to EOL */
		if (c == '#' && !in_quote)
		{
			while ((c = (*(*lineptr)++)) != '\0')
				;
			break;
		}

		if (buf >= end_buf)
		{
			*buf = '\0';
			ereport(elevel,
					(errcode(ERRCODE_CONFIG_FILE_ERROR),
					 errmsg("authentication file token too long, skipping: \"%s\"",
							start_buf)));
			*err_msg = "authentication file token too long";
			/* Discard remainder of line */
			while ((c = (*(*lineptr)++)) != '\0')
				;
			/* Un-eat the '\0', in case we're called again */
			(*lineptr)--;
			return false;
		}

		/* we do not pass back a terminating comma in the token */
		if (c == ',' && !in_quote)
		{
			*terminating_comma = true;
			break;
		}

		if (c != '"' || was_quote)
			*buf++ = c;

		/* Literal double-quote is two double-quotes */
		if (in_quote && c == '"')
			was_quote = !was_quote;
		else
			was_quote = false;

		if (c == '"')
		{
			in_quote = !in_quote;
			saw_quote = true;
			if (buf == start_buf)
				*initial_quote = true;
		}

		c = *(*lineptr)++;
	}

	/*
	 * Un-eat the char right after the token (critical in case it is '\0',
	 * else next call will read past end of string).
	 */
	(*lineptr)--;

	*buf = '\0';

	return (saw_quote || buf > start_buf);
}