#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct copy_options {int from; int program; int psql_inout; void* after_tofrom; int /*<<< orphan*/ * file; void* before_tofrom; } ;
struct TYPE_2__ {int /*<<< orphan*/  encoding; } ;

/* Variables and functions */
 int /*<<< orphan*/  expand_tilde (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  free_copy_options (struct copy_options*) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 struct copy_options* pg_malloc0 (int) ; 
 scalar_t__ pg_strcasecmp (char*,char*) ; 
 void* pg_strdup (char*) ; 
 TYPE_1__ pset ; 
 scalar_t__ standard_strings () ; 
 int /*<<< orphan*/  strip_quotes (char*,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 char* strtokx (char const*,char const*,char*,char*,char,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrcat (void**,char*) ; 

__attribute__((used)) static struct copy_options *
parse_slash_copy(const char *args)
{
	struct copy_options *result;
	char	   *token;
	const char *whitespace = " \t\n\r";
	char		nonstd_backslash = standard_strings() ? 0 : '\\';

	if (!args)
	{
		pg_log_error("\\copy: arguments required");
		return NULL;
	}

	result = pg_malloc0(sizeof(struct copy_options));

	result->before_tofrom = pg_strdup("");	/* initialize for appending */

	token = strtokx(args, whitespace, ".,()", "\"",
					0, false, false, pset.encoding);
	if (!token)
		goto error;

	/* The following can be removed when we drop 7.3 syntax support */
	if (pg_strcasecmp(token, "binary") == 0)
	{
		xstrcat(&result->before_tofrom, token);
		token = strtokx(NULL, whitespace, ".,()", "\"",
						0, false, false, pset.encoding);
		if (!token)
			goto error;
	}

	/* Handle COPY (query) case */
	if (token[0] == '(')
	{
		int			parens = 1;

		while (parens > 0)
		{
			xstrcat(&result->before_tofrom, " ");
			xstrcat(&result->before_tofrom, token);
			token = strtokx(NULL, whitespace, "()", "\"'",
							nonstd_backslash, true, false, pset.encoding);
			if (!token)
				goto error;
			if (token[0] == '(')
				parens++;
			else if (token[0] == ')')
				parens--;
		}
	}

	xstrcat(&result->before_tofrom, " ");
	xstrcat(&result->before_tofrom, token);
	token = strtokx(NULL, whitespace, ".,()", "\"",
					0, false, false, pset.encoding);
	if (!token)
		goto error;

	/*
	 * strtokx() will not have returned a multi-character token starting with
	 * '.', so we don't need strcmp() here.  Likewise for '(', etc, below.
	 */
	if (token[0] == '.')
	{
		/* handle schema . table */
		xstrcat(&result->before_tofrom, token);
		token = strtokx(NULL, whitespace, ".,()", "\"",
						0, false, false, pset.encoding);
		if (!token)
			goto error;
		xstrcat(&result->before_tofrom, token);
		token = strtokx(NULL, whitespace, ".,()", "\"",
						0, false, false, pset.encoding);
		if (!token)
			goto error;
	}

	if (token[0] == '(')
	{
		/* handle parenthesized column list */
		for (;;)
		{
			xstrcat(&result->before_tofrom, " ");
			xstrcat(&result->before_tofrom, token);
			token = strtokx(NULL, whitespace, "()", "\"",
							0, false, false, pset.encoding);
			if (!token)
				goto error;
			if (token[0] == ')')
				break;
		}
		xstrcat(&result->before_tofrom, " ");
		xstrcat(&result->before_tofrom, token);
		token = strtokx(NULL, whitespace, ".,()", "\"",
						0, false, false, pset.encoding);
		if (!token)
			goto error;
	}

	if (pg_strcasecmp(token, "from") == 0)
		result->from = true;
	else if (pg_strcasecmp(token, "to") == 0)
		result->from = false;
	else
		goto error;

	/* { 'filename' | PROGRAM 'command' | STDIN | STDOUT | PSTDIN | PSTDOUT } */
	token = strtokx(NULL, whitespace, ";", "'",
					0, false, false, pset.encoding);
	if (!token)
		goto error;

	if (pg_strcasecmp(token, "program") == 0)
	{
		int			toklen;

		token = strtokx(NULL, whitespace, ";", "'",
						0, false, false, pset.encoding);
		if (!token)
			goto error;

		/*
		 * The shell command must be quoted. This isn't fool-proof, but
		 * catches most quoting errors.
		 */
		toklen = strlen(token);
		if (token[0] != '\'' || toklen < 2 || token[toklen - 1] != '\'')
			goto error;

		strip_quotes(token, '\'', 0, pset.encoding);

		result->program = true;
		result->file = pg_strdup(token);
	}
	else if (pg_strcasecmp(token, "stdin") == 0 ||
			 pg_strcasecmp(token, "stdout") == 0)
	{
		result->file = NULL;
	}
	else if (pg_strcasecmp(token, "pstdin") == 0 ||
			 pg_strcasecmp(token, "pstdout") == 0)
	{
		result->psql_inout = true;
		result->file = NULL;
	}
	else
	{
		/* filename can be optionally quoted */
		strip_quotes(token, '\'', 0, pset.encoding);
		result->file = pg_strdup(token);
		expand_tilde(&result->file);
	}

	/* Collect the rest of the line (COPY options) */
	token = strtokx(NULL, "", NULL, NULL,
					0, false, false, pset.encoding);
	if (token)
		result->after_tofrom = pg_strdup(token);

	return result;

error:
	if (token)
		pg_log_error("\\copy: parse error at \"%s\"", token);
	else
		pg_log_error("\\copy: parse error at end of line");
	free_copy_options(result);

	return NULL;
}