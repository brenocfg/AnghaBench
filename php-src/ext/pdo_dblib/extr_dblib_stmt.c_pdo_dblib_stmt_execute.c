#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  column_count; int /*<<< orphan*/  row_count; int /*<<< orphan*/  active_query_string; scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_8__ {int /*<<< orphan*/  err; TYPE_3__* H; } ;
typedef  TYPE_2__ pdo_dblib_stmt ;
struct TYPE_9__ {int /*<<< orphan*/  link; } ;
typedef  TYPE_3__ pdo_dblib_db_handle ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DBCOUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ FAIL ; 
 scalar_t__ dbcmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbnumcols (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbsetuserdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dbsqlexec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdo_dblib_stmt_cursor_closer (TYPE_1__*) ; 
 int /*<<< orphan*/  pdo_dblib_stmt_next_rowset_no_cancel (TYPE_1__*) ; 

__attribute__((used)) static int pdo_dblib_stmt_execute(pdo_stmt_t *stmt)
{
	pdo_dblib_stmt *S = (pdo_dblib_stmt*)stmt->driver_data;
	pdo_dblib_db_handle *H = S->H;

	dbsetuserdata(H->link, (BYTE*) &S->err);

	pdo_dblib_stmt_cursor_closer(stmt);

	if (FAIL == dbcmd(H->link, stmt->active_query_string)) {
		return 0;
	}

	if (FAIL == dbsqlexec(H->link)) {
		return 0;
	}

	pdo_dblib_stmt_next_rowset_no_cancel(stmt);

	stmt->row_count = DBCOUNT(H->link);
	stmt->column_count = dbnumcols(H->link);

	return 1;
}