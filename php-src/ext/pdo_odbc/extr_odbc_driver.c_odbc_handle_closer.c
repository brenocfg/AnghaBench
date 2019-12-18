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
struct TYPE_5__ {int /*<<< orphan*/ * env; int /*<<< orphan*/ * dbc; } ;
typedef  TYPE_1__ pdo_odbc_db_handle ;
struct TYPE_6__ {int /*<<< orphan*/ * driver_data; int /*<<< orphan*/  is_persistent; } ;
typedef  TYPE_2__ pdo_dbh_t ;

/* Variables and functions */
 int /*<<< orphan*/  SQLDisconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SQLEndTran (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SQLFreeHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SQL_HANDLE_DBC ; 
 int /*<<< orphan*/  SQL_HANDLE_ENV ; 
 int /*<<< orphan*/ * SQL_NULL_HANDLE ; 
 int /*<<< orphan*/  SQL_ROLLBACK ; 
 int /*<<< orphan*/  pefree (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int odbc_handle_closer(pdo_dbh_t *dbh)
{
	pdo_odbc_db_handle *H = (pdo_odbc_db_handle*)dbh->driver_data;

	if (H->dbc != SQL_NULL_HANDLE) {
		SQLEndTran(SQL_HANDLE_DBC, H->dbc, SQL_ROLLBACK);
		SQLDisconnect(H->dbc);
		SQLFreeHandle(SQL_HANDLE_DBC, H->dbc);
		H->dbc = NULL;
	}
	SQLFreeHandle(SQL_HANDLE_ENV, H->env);
	H->env = NULL;
	pefree(H, dbh->is_persistent);
	dbh->driver_data = NULL;

	return 0;
}