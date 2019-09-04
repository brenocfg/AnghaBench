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
struct TYPE_4__ {scalar_t__ dbc; } ;
typedef  TYPE_1__ pdo_odbc_db_handle ;
struct TYPE_5__ {scalar_t__ auto_commit; scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_dbh_t ;
typedef  int /*<<< orphan*/  SQLPOINTER ;
typedef  scalar_t__ RETCODE ;

/* Variables and functions */
 scalar_t__ SQLEndTran (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SQLSetConnectAttr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SQL_ATTR_AUTOCOMMIT ; 
 scalar_t__ SQL_AUTOCOMMIT_ON ; 
 int /*<<< orphan*/  SQL_HANDLE_DBC ; 
 int /*<<< orphan*/  SQL_IS_INTEGER ; 
 int /*<<< orphan*/  SQL_ROLLBACK ; 
 scalar_t__ SQL_SUCCESS ; 
 scalar_t__ SQL_SUCCESS_WITH_INFO ; 
 int /*<<< orphan*/  pdo_odbc_drv_error (char*) ; 

__attribute__((used)) static int odbc_handle_rollback(pdo_dbh_t *dbh)
{
	pdo_odbc_db_handle *H = (pdo_odbc_db_handle *)dbh->driver_data;
	RETCODE rc;

	rc = SQLEndTran(SQL_HANDLE_DBC, H->dbc, SQL_ROLLBACK);

	if (rc != SQL_SUCCESS) {
		pdo_odbc_drv_error("SQLEndTran: Rollback");

		if (rc != SQL_SUCCESS_WITH_INFO) {
			return 0;
		}
	}
	if (dbh->auto_commit && H->dbc) {
		/* turn auto-commit back on again */
		rc = SQLSetConnectAttr(H->dbc, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_ON, SQL_IS_INTEGER);
		if (rc != SQL_SUCCESS) {
			pdo_odbc_drv_error("SQLSetConnectAttr AUTOCOMMIT = ON");
			return 0;
		}
	}

	return 1;
}