#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  db; int /*<<< orphan*/  vars; } ;
struct TYPE_5__ {char* data; } ;
typedef  int PsqlScanQuoteType ;
typedef  TYPE_1__ PQExpBufferData ;
typedef  int /*<<< orphan*/  ConditionalStack ;

/* Variables and functions */
 char* GetVariable (int /*<<< orphan*/ ,char const*) ; 
#define  PQUOTE_PLAIN 131 
#define  PQUOTE_SHELL_ARG 130 
#define  PQUOTE_SQL_IDENT 129 
#define  PQUOTE_SQL_LITERAL 128 
 char* PQerrorMessage (int /*<<< orphan*/ ) ; 
 char* PQescapeIdentifier (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 char* PQescapeLiteral (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQfreemem (char*) ; 
 int /*<<< orphan*/  appendShellStringNoError (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  conditional_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 int /*<<< orphan*/  pg_log_info (char*,char const*) ; 
 char* pg_strdup (char const*) ; 
 TYPE_2__ pset ; 
 int /*<<< orphan*/  strlen (char const*) ; 

char *
psql_get_variable(const char *varname, PsqlScanQuoteType quote,
				  void *passthrough)
{
	char	   *result = NULL;
	const char *value;

	/* In an inactive \if branch, suppress all variable substitutions */
	if (passthrough && !conditional_active((ConditionalStack) passthrough))
		return NULL;

	value = GetVariable(pset.vars, varname);
	if (!value)
		return NULL;

	switch (quote)
	{
		case PQUOTE_PLAIN:
			result = pg_strdup(value);
			break;
		case PQUOTE_SQL_LITERAL:
		case PQUOTE_SQL_IDENT:
			{
				/*
				 * For these cases, we use libpq's quoting functions, which
				 * assume the string is in the connection's client encoding.
				 */
				char	   *escaped_value;

				if (!pset.db)
				{
					pg_log_error("cannot escape without active connection");
					return NULL;
				}

				if (quote == PQUOTE_SQL_LITERAL)
					escaped_value =
						PQescapeLiteral(pset.db, value, strlen(value));
				else
					escaped_value =
						PQescapeIdentifier(pset.db, value, strlen(value));

				if (escaped_value == NULL)
				{
					const char *error = PQerrorMessage(pset.db);

					pg_log_info("%s", error);
					return NULL;
				}

				/*
				 * Rather than complicate the lexer's API with a notion of
				 * which free() routine to use, just pay the price of an extra
				 * strdup().
				 */
				result = pg_strdup(escaped_value);
				PQfreemem(escaped_value);
				break;
			}
		case PQUOTE_SHELL_ARG:
			{
				/*
				 * For this we use appendShellStringNoError, which is
				 * encoding-agnostic, which is fine since the shell probably
				 * is too.  In any case, the only special character is "'",
				 * which is not known to appear in valid multibyte characters.
				 */
				PQExpBufferData buf;

				initPQExpBuffer(&buf);
				if (!appendShellStringNoError(&buf, value))
				{
					pg_log_error("shell command argument contains a newline or carriage return: \"%s\"",
								 value);
					free(buf.data);
					return NULL;
				}
				result = buf.data;
				break;
			}

			/* No default: we want a compiler warning for missing cases */
	}

	return result;
}