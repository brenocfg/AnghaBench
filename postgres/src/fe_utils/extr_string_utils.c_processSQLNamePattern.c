#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* data; int len; } ;
typedef  TYPE_1__ PQExpBufferData ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int PQclientEncoding (int /*<<< orphan*/ *) ; 
 int PQmblen (char const*,int) ; 
 int PQserverVersion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WHEREAND () ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_1__*,char const) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  appendStringLiteralConn (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 scalar_t__ isupper (unsigned char) ; 
 char pg_tolower (unsigned char) ; 
 int /*<<< orphan*/  resetPQExpBuffer (TYPE_1__*) ; 
 scalar_t__ strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_1__*) ; 

bool
processSQLNamePattern(PGconn *conn, PQExpBuffer buf, const char *pattern,
					  bool have_where, bool force_escape,
					  const char *schemavar, const char *namevar,
					  const char *altnamevar, const char *visibilityrule)
{
	PQExpBufferData schemabuf;
	PQExpBufferData namebuf;
	int			encoding = PQclientEncoding(conn);
	bool		inquotes;
	const char *cp;
	int			i;
	bool		added_clause = false;

#define WHEREAND() \
	(appendPQExpBufferStr(buf, have_where ? "  AND " : "WHERE "), \
	 have_where = true, added_clause = true)

	if (pattern == NULL)
	{
		/* Default: select all visible objects */
		if (visibilityrule)
		{
			WHEREAND();
			appendPQExpBuffer(buf, "%s\n", visibilityrule);
		}
		return added_clause;
	}

	initPQExpBuffer(&schemabuf);
	initPQExpBuffer(&namebuf);

	/*
	 * Parse the pattern, converting quotes and lower-casing unquoted letters.
	 * Also, adjust shell-style wildcard characters into regexp notation.
	 *
	 * We surround the pattern with "^(...)$" to force it to match the whole
	 * string, as per SQL practice.  We have to have parens in case the string
	 * contains "|", else the "^" and "$" will be bound into the first and
	 * last alternatives which is not what we want.
	 *
	 * Note: the result of this pass is the actual regexp pattern(s) we want
	 * to execute.  Quoting/escaping into SQL literal format will be done
	 * below using appendStringLiteralConn().
	 */
	appendPQExpBufferStr(&namebuf, "^(");

	inquotes = false;
	cp = pattern;

	while (*cp)
	{
		char		ch = *cp;

		if (ch == '"')
		{
			if (inquotes && cp[1] == '"')
			{
				/* emit one quote, stay in inquotes mode */
				appendPQExpBufferChar(&namebuf, '"');
				cp++;
			}
			else
				inquotes = !inquotes;
			cp++;
		}
		else if (!inquotes && isupper((unsigned char) ch))
		{
			appendPQExpBufferChar(&namebuf,
								  pg_tolower((unsigned char) ch));
			cp++;
		}
		else if (!inquotes && ch == '*')
		{
			appendPQExpBufferStr(&namebuf, ".*");
			cp++;
		}
		else if (!inquotes && ch == '?')
		{
			appendPQExpBufferChar(&namebuf, '.');
			cp++;
		}
		else if (!inquotes && ch == '.')
		{
			/* Found schema/name separator, move current pattern to schema */
			resetPQExpBuffer(&schemabuf);
			appendPQExpBufferStr(&schemabuf, namebuf.data);
			resetPQExpBuffer(&namebuf);
			appendPQExpBufferStr(&namebuf, "^(");
			cp++;
		}
		else if (ch == '$')
		{
			/*
			 * Dollar is always quoted, whether inside quotes or not. The
			 * reason is that it's allowed in SQL identifiers, so there's a
			 * significant use-case for treating it literally, while because
			 * we anchor the pattern automatically there is no use-case for
			 * having it possess its regexp meaning.
			 */
			appendPQExpBufferStr(&namebuf, "\\$");
			cp++;
		}
		else
		{
			/*
			 * Ordinary data character, transfer to pattern
			 *
			 * Inside double quotes, or at all times if force_escape is true,
			 * quote regexp special characters with a backslash to avoid
			 * regexp errors.  Outside quotes, however, let them pass through
			 * as-is; this lets knowledgeable users build regexp expressions
			 * that are more powerful than shell-style patterns.
			 */
			if ((inquotes || force_escape) &&
				strchr("|*+?()[]{}.^$\\", ch))
				appendPQExpBufferChar(&namebuf, '\\');
			i = PQmblen(cp, encoding);
			while (i-- && *cp)
			{
				appendPQExpBufferChar(&namebuf, *cp);
				cp++;
			}
		}
	}

	/*
	 * Now decide what we need to emit.  We may run under a hostile
	 * search_path, so qualify EVERY name.  Note there will be a leading "^("
	 * in the patterns in any case.
	 *
	 * We want the regex matches to use the database's default collation where
	 * collation-sensitive behavior is required (for example, which characters
	 * match '\w').  That happened by default before PG v12, but if the server
	 * is >= v12 then we need to force it through explicit COLLATE clauses,
	 * otherwise the "C" collation attached to "name" catalog columns wins.
	 */
	if (namebuf.len > 2)
	{
		/* We have a name pattern, so constrain the namevar(s) */

		appendPQExpBufferStr(&namebuf, ")$");
		/* Optimize away a "*" pattern */
		if (strcmp(namebuf.data, "^(.*)$") != 0)
		{
			WHEREAND();
			if (altnamevar)
			{
				appendPQExpBuffer(buf,
								  "(%s OPERATOR(pg_catalog.~) ", namevar);
				appendStringLiteralConn(buf, namebuf.data, conn);
				if (PQserverVersion(conn) >= 120000)
					appendPQExpBufferStr(buf, " COLLATE pg_catalog.default");
				appendPQExpBuffer(buf,
								  "\n        OR %s OPERATOR(pg_catalog.~) ",
								  altnamevar);
				appendStringLiteralConn(buf, namebuf.data, conn);
				if (PQserverVersion(conn) >= 120000)
					appendPQExpBufferStr(buf, " COLLATE pg_catalog.default");
				appendPQExpBufferStr(buf, ")\n");
			}
			else
			{
				appendPQExpBuffer(buf, "%s OPERATOR(pg_catalog.~) ", namevar);
				appendStringLiteralConn(buf, namebuf.data, conn);
				if (PQserverVersion(conn) >= 120000)
					appendPQExpBufferStr(buf, " COLLATE pg_catalog.default");
				appendPQExpBufferChar(buf, '\n');
			}
		}
	}

	if (schemabuf.len > 2)
	{
		/* We have a schema pattern, so constrain the schemavar */

		appendPQExpBufferStr(&schemabuf, ")$");
		/* Optimize away a "*" pattern */
		if (strcmp(schemabuf.data, "^(.*)$") != 0 && schemavar)
		{
			WHEREAND();
			appendPQExpBuffer(buf, "%s OPERATOR(pg_catalog.~) ", schemavar);
			appendStringLiteralConn(buf, schemabuf.data, conn);
			if (PQserverVersion(conn) >= 120000)
				appendPQExpBufferStr(buf, " COLLATE pg_catalog.default");
			appendPQExpBufferChar(buf, '\n');
		}
	}
	else
	{
		/* No schema pattern given, so select only visible objects */
		if (visibilityrule)
		{
			WHEREAND();
			appendPQExpBuffer(buf, "%s\n", visibilityrule);
		}
	}

	termPQExpBuffer(&schemabuf);
	termPQExpBuffer(&namebuf);

	return added_clause;
#undef WHEREAND
}