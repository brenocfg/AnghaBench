#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  query ;
typedef  int /*<<< orphan*/  qbuf ;
struct TYPE_9__ {scalar_t__ status; int /*<<< orphan*/  pversion; } ;
struct TYPE_8__ {scalar_t__ resultStatus; } ;
typedef  TYPE_1__ PGresult ;
typedef  TYPE_2__ PGconn ;

/* Variables and functions */
 scalar_t__ CONNECTION_OK ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 int PG_PROTOCOL_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQclear (TYPE_1__*) ; 
 TYPE_1__* PQexec (TYPE_2__*,char*) ; 
 char* pg_encoding_to_char (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_get_encoding_from_locale (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pqSaveParameterStatus (TYPE_2__*,char*,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char const*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 

int
PQsetClientEncoding(PGconn *conn, const char *encoding)
{
	char		qbuf[128];
	static const char query[] = "set client_encoding to '%s'";
	PGresult   *res;
	int			status;

	if (!conn || conn->status != CONNECTION_OK)
		return -1;

	if (!encoding)
		return -1;

	/* Resolve special "auto" value from the locale */
	if (strcmp(encoding, "auto") == 0)
		encoding = pg_encoding_to_char(pg_get_encoding_from_locale(NULL, true));

	/* check query buffer overflow */
	if (sizeof(qbuf) < (sizeof(query) + strlen(encoding)))
		return -1;

	/* ok, now send a query */
	sprintf(qbuf, query, encoding);
	res = PQexec(conn, qbuf);

	if (res == NULL)
		return -1;
	if (res->resultStatus != PGRES_COMMAND_OK)
		status = -1;
	else
	{
		/*
		 * In protocol 2 we have to assume the setting will stick, and adjust
		 * our state immediately.  In protocol 3 and up we can rely on the
		 * backend to report the parameter value, and we'll change state at
		 * that time.
		 */
		if (PG_PROTOCOL_MAJOR(conn->pversion) < 3)
			pqSaveParameterStatus(conn, "client_encoding", encoding);
		status = 0;				/* everything is ok */
	}
	PQclear(res);
	return status;
}