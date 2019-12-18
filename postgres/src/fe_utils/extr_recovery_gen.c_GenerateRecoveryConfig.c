#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_16__ {char* keyword; char* val; } ;
typedef  TYPE_1__ PQconninfoOption ;
typedef  TYPE_2__ PQExpBufferData ;
typedef  TYPE_2__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ MINIMUM_VERSION_FOR_RECOVERY_GUC ; 
 scalar_t__ PQExpBufferBroken (TYPE_2__*) ; 
 scalar_t__ PQExpBufferDataBroken (TYPE_2__) ; 
 TYPE_1__* PQconninfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQconninfoFree (TYPE_1__*) ; 
 scalar_t__ PQserverVersion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendConnStrVal (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_2__*,char) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_2__*,char*) ; 
 TYPE_2__* createPQExpBuffer () ; 
 char* escape_quotes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  pg_log_error (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_2__*) ; 

PQExpBuffer
GenerateRecoveryConfig(PGconn *pgconn, char *replication_slot)
{
	PQconninfoOption *connOptions;
	PQExpBufferData conninfo_buf;
	char	   *escaped;
	PQExpBuffer contents;

	Assert(pgconn != NULL);

	contents = createPQExpBuffer();
	if (!contents)
	{
		pg_log_error("out of memory");
		exit(1);
	}

	/*
	 * In PostgreSQL 12 and newer versions, standby_mode is gone, replaced by
	 * standby.signal to trigger a standby state at recovery.
	 */
	if (PQserverVersion(pgconn) < MINIMUM_VERSION_FOR_RECOVERY_GUC)
		appendPQExpBufferStr(contents, "standby_mode = 'on'\n");

	connOptions = PQconninfo(pgconn);
	if (connOptions == NULL)
	{
		pg_log_error("out of memory");
		exit(1);
	}

	initPQExpBuffer(&conninfo_buf);
	for (PQconninfoOption *opt = connOptions; opt && opt->keyword; opt++)
	{
		/* Omit empty settings and those libpqwalreceiver overrides. */
		if (strcmp(opt->keyword, "replication") == 0 ||
			strcmp(opt->keyword, "dbname") == 0 ||
			strcmp(opt->keyword, "fallback_application_name") == 0 ||
			(opt->val == NULL) ||
			(opt->val != NULL && opt->val[0] == '\0'))
			continue;

		/* Separate key-value pairs with spaces */
		if (conninfo_buf.len != 0)
			appendPQExpBufferChar(&conninfo_buf, ' ');

		/*
		 * Write "keyword=value" pieces, the value string is escaped and/or
		 * quoted if necessary.
		 */
		appendPQExpBuffer(&conninfo_buf, "%s=", opt->keyword);
		appendConnStrVal(&conninfo_buf, opt->val);
	}
	if (PQExpBufferDataBroken(conninfo_buf))
	{
		pg_log_error("out of memory");
		exit(1);
	}

	/*
	 * Escape the connection string, so that it can be put in the config file.
	 * Note that this is different from the escaping of individual connection
	 * options above!
	 */
	escaped = escape_quotes(conninfo_buf.data);
	termPQExpBuffer(&conninfo_buf);
	appendPQExpBuffer(contents, "primary_conninfo = '%s'\n", escaped);
	free(escaped);

	if (replication_slot)
	{
		/* unescaped: ReplicationSlotValidateName allows [a-z0-9_] only */
		appendPQExpBuffer(contents, "primary_slot_name = '%s'\n",
						  replication_slot);
	}

	if (PQExpBufferBroken(contents))
	{
		pg_log_error("out of memory");
		exit(1);
	}

	PQconninfoFree(connOptions);

	return contents;
}