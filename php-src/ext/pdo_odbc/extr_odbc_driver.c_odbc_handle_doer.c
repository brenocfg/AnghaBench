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
typedef  int zend_long ;
struct TYPE_4__ {int /*<<< orphan*/  dbc; } ;
typedef  TYPE_1__ pdo_odbc_db_handle ;
struct TYPE_5__ {scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_dbh_t ;
typedef  int SQLLEN ;
typedef  scalar_t__ RETCODE ;
typedef  int /*<<< orphan*/  PDO_ODBC_HSTMT ;

/* Variables and functions */
 scalar_t__ SQLAllocHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SQLExecDirect (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  SQLFreeHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SQLRowCount (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  SQL_HANDLE_STMT ; 
 scalar_t__ SQL_NO_DATA ; 
 scalar_t__ SQL_SUCCESS ; 
 scalar_t__ SQL_SUCCESS_WITH_INFO ; 
 int /*<<< orphan*/  pdo_odbc_doer_error (char*) ; 
 int /*<<< orphan*/  pdo_odbc_drv_error (char*) ; 

__attribute__((used)) static zend_long odbc_handle_doer(pdo_dbh_t *dbh, const char *sql, size_t sql_len)
{
	pdo_odbc_db_handle *H = (pdo_odbc_db_handle *)dbh->driver_data;
	RETCODE rc;
	SQLLEN row_count = -1;
	PDO_ODBC_HSTMT	stmt;

	rc = SQLAllocHandle(SQL_HANDLE_STMT, H->dbc, &stmt);
	if (rc != SQL_SUCCESS) {
		pdo_odbc_drv_error("SQLAllocHandle: STMT");
		return -1;
	}

	rc = SQLExecDirect(stmt, (char *)sql, sql_len);

	if (rc == SQL_NO_DATA) {
		/* If SQLExecDirect executes a searched update or delete statement that
		 * does not affect any rows at the data source, the call to
		 * SQLExecDirect returns SQL_NO_DATA. */
		row_count = 0;
		goto out;
	}

	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
		pdo_odbc_doer_error("SQLExecDirect");
		goto out;
	}

	rc = SQLRowCount(stmt, &row_count);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
		pdo_odbc_doer_error("SQLRowCount");
		goto out;
	}
	if (row_count == -1) {
		row_count = 0;
	}
out:
	SQLFreeHandle(SQL_HANDLE_STMT, stmt);
	return row_count;
}