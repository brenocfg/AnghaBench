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
typedef  int /*<<< orphan*/  zend_long ;
struct TYPE_4__ {int /*<<< orphan*/  error_code; scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_5__ {int /*<<< orphan*/  stmt; } ;
typedef  TYPE_2__ pdo_odbc_stmt ;
typedef  enum pdo_fetch_orientation { ____Placeholder_pdo_fetch_orientation } pdo_fetch_orientation ;
typedef  int /*<<< orphan*/  SQLSMALLINT ;
typedef  scalar_t__ RETCODE ;

/* Variables and functions */
#define  PDO_FETCH_ORI_ABS 133 
#define  PDO_FETCH_ORI_FIRST 132 
#define  PDO_FETCH_ORI_LAST 131 
#define  PDO_FETCH_ORI_NEXT 130 
#define  PDO_FETCH_ORI_PRIOR 129 
#define  PDO_FETCH_ORI_REL 128 
 scalar_t__ SQLFetchScroll (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SQL_FETCH_ABSOLUTE ; 
 int /*<<< orphan*/  SQL_FETCH_FIRST ; 
 int /*<<< orphan*/  SQL_FETCH_LAST ; 
 int /*<<< orphan*/  SQL_FETCH_NEXT ; 
 int /*<<< orphan*/  SQL_FETCH_PRIOR ; 
 int /*<<< orphan*/  SQL_FETCH_RELATIVE ; 
 scalar_t__ SQL_NO_DATA ; 
 scalar_t__ SQL_SUCCESS ; 
 scalar_t__ SQL_SUCCESS_WITH_INFO ; 
 int /*<<< orphan*/  pdo_odbc_stmt_error (char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int odbc_stmt_fetch(pdo_stmt_t *stmt,
	enum pdo_fetch_orientation ori, zend_long offset)
{
	RETCODE rc;
	SQLSMALLINT odbcori;
	pdo_odbc_stmt *S = (pdo_odbc_stmt*)stmt->driver_data;

	switch (ori) {
		case PDO_FETCH_ORI_NEXT:	odbcori = SQL_FETCH_NEXT; break;
		case PDO_FETCH_ORI_PRIOR:	odbcori = SQL_FETCH_PRIOR; break;
		case PDO_FETCH_ORI_FIRST:	odbcori = SQL_FETCH_FIRST; break;
		case PDO_FETCH_ORI_LAST:	odbcori = SQL_FETCH_LAST; break;
		case PDO_FETCH_ORI_ABS:		odbcori = SQL_FETCH_ABSOLUTE; break;
		case PDO_FETCH_ORI_REL:		odbcori = SQL_FETCH_RELATIVE; break;
		default:
			strcpy(stmt->error_code, "HY106");
			return 0;
	}
	rc = SQLFetchScroll(S->stmt, odbcori, offset);

	if (rc == SQL_SUCCESS) {
		return 1;
	}
	if (rc == SQL_SUCCESS_WITH_INFO) {
		pdo_odbc_stmt_error("SQLFetchScroll");
		return 1;
	}

	if (rc == SQL_NO_DATA) {
		/* pdo_odbc_stmt_error("SQLFetchScroll"); */
		return 0;
	}

	pdo_odbc_stmt_error("SQLFetchScroll");

	return 0;
}