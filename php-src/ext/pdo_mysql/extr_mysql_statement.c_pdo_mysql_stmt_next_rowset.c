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
typedef  scalar_t__ zend_long ;
struct TYPE_7__ {int column_count; scalar_t__ row_count; scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_8__ {int /*<<< orphan*/ * result; scalar_t__ stmt; int /*<<< orphan*/  fields; TYPE_3__* H; } ;
typedef  TYPE_2__ pdo_mysql_stmt ;
struct TYPE_9__ {int /*<<< orphan*/  server; scalar_t__ buffered; int /*<<< orphan*/  emulate_prepare; } ;
typedef  TYPE_3__ pdo_mysql_db_handle ;

/* Variables and functions */
 scalar_t__ FAIL ; 
 int /*<<< orphan*/  PDO_DBG_ENTER (char*) ; 
 int /*<<< orphan*/  PDO_DBG_INF_FMT (char*,scalar_t__) ; 
 int /*<<< orphan*/  PDO_DBG_RETURN (int) ; 
 int /*<<< orphan*/  mysql_fetch_fields (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mysql_free_result (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mysql_more_results (int /*<<< orphan*/ ) ; 
 scalar_t__ mysql_next_result (int /*<<< orphan*/ ) ; 
 scalar_t__ mysql_num_fields (int /*<<< orphan*/ *) ; 
 scalar_t__ mysql_stmt_affected_rows (scalar_t__) ; 
 int mysql_stmt_field_count (scalar_t__) ; 
 int /*<<< orphan*/  mysql_stmt_free_result (scalar_t__) ; 
 scalar_t__ mysql_stmt_store_result (scalar_t__) ; 
 int /*<<< orphan*/  mysqlnd_stmt_bind_one_result (scalar_t__,int) ; 
 int /*<<< orphan*/  mysqlnd_stmt_more_results (scalar_t__) ; 
 scalar_t__ mysqlnd_stmt_next_result (scalar_t__) ; 
 int /*<<< orphan*/ * mysqlnd_stmt_result_metadata (scalar_t__) ; 
 int /*<<< orphan*/  pdo_mysql_error_stmt (TYPE_1__*) ; 
 int pdo_mysql_fill_stmt_from_result (TYPE_1__*) ; 

__attribute__((used)) static int pdo_mysql_stmt_next_rowset(pdo_stmt_t *stmt) /* {{{ */
{
	pdo_mysql_stmt *S = (pdo_mysql_stmt*)stmt->driver_data;
	pdo_mysql_db_handle *H = S->H;
#if PDO_USE_MYSQLND
	zend_long row_count;
#endif
	PDO_DBG_ENTER("pdo_mysql_stmt_next_rowset");
	PDO_DBG_INF_FMT("stmt=%p", S->stmt);

#if PDO_USE_MYSQLND
	if (!H->emulate_prepare) {
		if (!mysqlnd_stmt_more_results(S->stmt)) {
			PDO_DBG_RETURN(0);
		}
		if (mysqlnd_stmt_next_result(S->stmt)) {
			PDO_DBG_RETURN(0);
		}

		if (!mysqlnd_stmt_more_results(S->stmt)) {
			/*
			MySQL gives us n + 1 result sets for
			CALL proc() and n result sets returned by the proc itself.
			Result set n + 1 is about the procedure call itself.
			As the PDO emulation does not return it, we skip it as well
			*/
			PDO_DBG_RETURN(0);
		}

		/* TODO - this code is stolen from execute() - see above */
		if (S->result) {
			mysql_free_result(S->result);
			S->result = NULL;
		}
		{
			/* for SHOW/DESCRIBE and others the column/field count is not available before execute */
			int i;

			stmt->column_count = mysql_stmt_field_count(S->stmt);
			for (i = 0; i < stmt->column_count; i++) {
				mysqlnd_stmt_bind_one_result(S->stmt, i);
			}
		}

		S->result = mysqlnd_stmt_result_metadata(S->stmt);
		if (S->result) {
			S->fields = mysql_fetch_fields(S->result);

			/* if buffered, pre-fetch all the data */
			if (H->buffered) {
				if (mysql_stmt_store_result(S->stmt)) {
					PDO_DBG_RETURN(1);
				}
			}
		}
		row_count = (zend_long) mysql_stmt_affected_rows(S->stmt);
		if (row_count != (zend_long)-1) {
			stmt->row_count = row_count;
		}
		PDO_DBG_RETURN(1);
	}
#endif

/* ensure that we free any previous unfetched results */
#ifndef PDO_USE_MYSQLND
	if (S->stmt) {
		if (S->result) {
			stmt->column_count = (int)mysql_num_fields(S->result);
		}
		mysql_stmt_free_result(S->stmt);
	}
#endif
	if (S->result) {
		mysql_free_result(S->result);
		S->result = NULL;
	}

	if (!mysql_more_results(H->server)) {
		/* No more results */
		PDO_DBG_RETURN(0);
	}
#if PDO_USE_MYSQLND
	if (mysql_next_result(H->server) == FAIL) {
		pdo_mysql_error_stmt(stmt);
		PDO_DBG_RETURN(0);
	} else {
		PDO_DBG_RETURN(pdo_mysql_fill_stmt_from_result(stmt));
	}
#else
	if (mysql_next_result(H->server) > 0) {
		pdo_mysql_error_stmt(stmt);
		PDO_DBG_RETURN(0);
	} else {
		PDO_DBG_RETURN(pdo_mysql_fill_stmt_from_result(stmt));
	}
#endif
}