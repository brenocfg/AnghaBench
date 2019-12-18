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
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 scalar_t__ PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResetCancelConn () ; 
 int /*<<< orphan*/  SetCancelConn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

bool
executeMaintenanceCommand(PGconn *conn, const char *query, bool echo)
{
	PGresult   *res;
	bool		r;

	if (echo)
		printf("%s\n", query);

	SetCancelConn(conn);
	res = PQexec(conn, query);
	ResetCancelConn();

	r = (res && PQresultStatus(res) == PGRES_COMMAND_OK);

	if (res)
		PQclear(res);

	return r;
}