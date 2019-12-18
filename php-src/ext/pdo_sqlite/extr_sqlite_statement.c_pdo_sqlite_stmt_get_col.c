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
struct TYPE_5__ {scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_6__ {int /*<<< orphan*/  stmt; } ;
typedef  TYPE_2__ pdo_sqlite_stmt ;

/* Variables and functions */
#define  SQLITE_BLOB 129 
#define  SQLITE_NULL 128 
 int /*<<< orphan*/  pdo_sqlite_error_stmt (TYPE_1__*) ; 
 scalar_t__ sqlite3_column_blob (int /*<<< orphan*/ ,int) ; 
 size_t sqlite3_column_bytes (int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ ,int) ; 
 int sqlite3_column_type (int /*<<< orphan*/ ,int) ; 
 int sqlite3_data_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pdo_sqlite_stmt_get_col(pdo_stmt_t *stmt, int colno, char **ptr, size_t *len, int *caller_frees)
{
	pdo_sqlite_stmt *S = (pdo_sqlite_stmt*)stmt->driver_data;
	if (!S->stmt) {
		return 0;
	}
	if(colno >= sqlite3_data_count(S->stmt)) {
		/* error invalid column */
		pdo_sqlite_error_stmt(stmt);
		return 0;
	}
	switch (sqlite3_column_type(S->stmt, colno)) {
		case SQLITE_NULL:
			*ptr = NULL;
			*len = 0;
			return 1;

		case SQLITE_BLOB:
			*ptr = (char*)sqlite3_column_blob(S->stmt, colno);
			*len = sqlite3_column_bytes(S->stmt, colno);
			return 1;

		default:
			*ptr = (char*)sqlite3_column_text(S->stmt, colno);
			*len = sqlite3_column_bytes(S->stmt, colno);
			return 1;
	}
}