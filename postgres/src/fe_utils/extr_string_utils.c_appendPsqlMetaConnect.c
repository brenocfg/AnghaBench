#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char const* data; } ;
typedef  TYPE_1__ PQExpBufferData ;
typedef  TYPE_1__* PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  appendConnStrVal (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 char* fmtId (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_1__*) ; 

void
appendPsqlMetaConnect(PQExpBuffer buf, const char *dbname)
{
	const char *s;
	bool complex;

	/*
	 * If the name is plain ASCII characters, emit a trivial "\connect "foo"".
	 * For other names, even many not technically requiring it, skip to the
	 * general case.  No database has a zero-length name.
	 */
	complex = false;

	for (s = dbname; *s; s++)
	{
		if (*s == '\n' || *s == '\r')
		{
			fprintf(stderr,
					_("database name contains a newline or carriage return: \"%s\"\n"),
					dbname);
			exit(EXIT_FAILURE);
		}

		if (!((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z') ||
			  (*s >= '0' && *s <= '9') || *s == '_' || *s == '.'))
		{
			complex = true;
		}
	}

	appendPQExpBufferStr(buf, "\\connect ");
	if (complex)
	{
		PQExpBufferData connstr;

		initPQExpBuffer(&connstr);
		appendPQExpBufferStr(&connstr, "dbname=");
		appendConnStrVal(&connstr, dbname);

		appendPQExpBufferStr(buf, "-reuse-previous=on ");

		/*
		 * As long as the name does not contain a newline, SQL identifier
		 * quoting satisfies the psql meta-command parser.  Prefer not to
		 * involve psql-interpreted single quotes, which behaved differently
		 * before PostgreSQL 9.2.
		 */
		appendPQExpBufferStr(buf, fmtId(connstr.data));

		termPQExpBuffer(&connstr);
	}
	else
		appendPQExpBufferStr(buf, fmtId(dbname));
	appendPQExpBufferChar(buf, '\n');
}