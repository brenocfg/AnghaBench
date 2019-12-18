#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* zend_long ;
struct TYPE_6__ {int column_count; void* row_count; scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_7__ {int /*<<< orphan*/ * result; int /*<<< orphan*/  fields; TYPE_3__* H; } ;
typedef  TYPE_2__ pdo_mysql_stmt ;
struct TYPE_8__ {int /*<<< orphan*/  server; int /*<<< orphan*/  buffered; } ;
typedef  TYPE_3__ pdo_mysql_db_handle ;
typedef  scalar_t__ my_ulonglong ;

/* Variables and functions */
 int /*<<< orphan*/  PDO_DBG_ENTER (char*) ; 
 int /*<<< orphan*/  PDO_DBG_RETURN (int) ; 
 scalar_t__ mysql_affected_rows (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mysql_fetch_fields (int /*<<< orphan*/ *) ; 
 scalar_t__ mysql_num_fields (int /*<<< orphan*/ *) ; 
 scalar_t__ mysql_num_rows (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mysql_store_result (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mysql_use_result (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdo_mysql_error_stmt (TYPE_1__*) ; 

__attribute__((used)) static int pdo_mysql_fill_stmt_from_result(pdo_stmt_t *stmt) /* {{{ */
{
	pdo_mysql_stmt *S = (pdo_mysql_stmt*)stmt->driver_data;
	pdo_mysql_db_handle *H = S->H;
	my_ulonglong row_count;
	PDO_DBG_ENTER("pdo_mysql_fill_stmt_from_result");

	row_count = mysql_affected_rows(H->server);
	if (row_count == (my_ulonglong)-1) {
		/* we either have a query that returned a result set or an error occurred
		   lets see if we have access to a result set */
		if (!H->buffered) {
			S->result = mysql_use_result(H->server);
		} else {
			S->result = mysql_store_result(H->server);
		}
		if (NULL == S->result) {
			pdo_mysql_error_stmt(stmt);
			PDO_DBG_RETURN(0);
		}

		stmt->row_count = (zend_long) mysql_num_rows(S->result);
		stmt->column_count = (int) mysql_num_fields(S->result);
		S->fields = mysql_fetch_fields(S->result);
	} else {
		/* this was a DML or DDL query (INSERT, UPDATE, DELETE, ... */
		stmt->row_count = (zend_long) row_count;
	}

	PDO_DBG_RETURN(1);
}