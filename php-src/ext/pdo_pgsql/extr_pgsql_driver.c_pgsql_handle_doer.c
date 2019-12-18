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
typedef  int zend_long ;
struct TYPE_5__ {int /*<<< orphan*/  pgoid; int /*<<< orphan*/  server; } ;
typedef  TYPE_1__ pdo_pgsql_db_handle ;
struct TYPE_6__ {scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_dbh_t ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  scalar_t__ ExecStatusType ;

/* Variables and functions */
 scalar_t__ PGRES_COMMAND_OK ; 
 scalar_t__ PGRES_FATAL_ERROR ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQcmdTuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  PQoidValue (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZEND_ATOL (int,int /*<<< orphan*/ ) ; 
 int Z_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdo_pgsql_error (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdo_pgsql_sqlstate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_long pgsql_handle_doer(pdo_dbh_t *dbh, const char *sql, size_t sql_len)
{
	pdo_pgsql_db_handle *H = (pdo_pgsql_db_handle *)dbh->driver_data;
	PGresult *res;
	zend_long ret = 1;
	ExecStatusType qs;

	if (!(res = PQexec(H->server, sql))) {
		/* fatal error */
		pdo_pgsql_error(dbh, PGRES_FATAL_ERROR, NULL);
		return -1;
	}
	qs = PQresultStatus(res);
	if (qs != PGRES_COMMAND_OK && qs != PGRES_TUPLES_OK) {
		pdo_pgsql_error(dbh, qs, pdo_pgsql_sqlstate(res));
		PQclear(res);
		return -1;
	}
	H->pgoid = PQoidValue(res);
	if (qs == PGRES_COMMAND_OK) {
		ZEND_ATOL(ret, PQcmdTuples(res));
	} else {
		ret = Z_L(0);
	}
	PQclear(res);

	return ret;
}