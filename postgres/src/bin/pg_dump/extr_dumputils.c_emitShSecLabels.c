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
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 char* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBuffer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  appendStringLiteralConn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmtId (char const*) ; 

void
emitShSecLabels(PGconn *conn, PGresult *res, PQExpBuffer buffer,
				const char *objtype, const char *objname)
{
	int			i;

	for (i = 0; i < PQntuples(res); i++)
	{
		char	   *provider = PQgetvalue(res, i, 0);
		char	   *label = PQgetvalue(res, i, 1);

		/* must use fmtId result before calling it again */
		appendPQExpBuffer(buffer,
						  "SECURITY LABEL FOR %s ON %s",
						  fmtId(provider), objtype);
		appendPQExpBuffer(buffer,
						  " %s IS ",
						  fmtId(objname));
		appendStringLiteralConn(buffer, label, conn);
		appendPQExpBufferStr(buffer, ";\n");
	}
}