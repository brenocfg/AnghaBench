#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t whichhost; int /*<<< orphan*/  pgpassfile; int /*<<< orphan*/  errorMessage; scalar_t__ result; TYPE_1__* connhost; scalar_t__ password_needed; } ;
struct TYPE_4__ {int /*<<< orphan*/ * password; } ;
typedef  TYPE_2__ PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PASSWORD ; 
 int /*<<< orphan*/  PG_DIAG_SQLSTATE ; 
 char* PQresultErrorField (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pgpassfileWarning(PGconn *conn)
{
	/* If it was 'invalid authorization', add pgpassfile mention */
	/* only works with >= 9.0 servers */
	if (conn->password_needed &&
		conn->connhost[conn->whichhost].password != NULL &&
		conn->result)
	{
		const char *sqlstate = PQresultErrorField(conn->result,
												  PG_DIAG_SQLSTATE);

		if (sqlstate && strcmp(sqlstate, ERRCODE_INVALID_PASSWORD) == 0)
			appendPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("password retrieved from file \"%s\"\n"),
							  conn->pgpassfile);
	}
}