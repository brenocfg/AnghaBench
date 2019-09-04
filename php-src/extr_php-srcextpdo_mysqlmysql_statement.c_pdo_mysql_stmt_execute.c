#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  active_query_stringlen; int /*<<< orphan*/  active_query_string; scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_9__ {int /*<<< orphan*/ * result; scalar_t__ stmt; TYPE_3__* H; } ;
typedef  TYPE_2__ pdo_mysql_stmt ;
struct TYPE_10__ {int /*<<< orphan*/  server; } ;
typedef  TYPE_3__ pdo_mysql_db_handle ;

/* Variables and functions */
 int /*<<< orphan*/  PDO_DBG_ENTER (char*) ; 
 int /*<<< orphan*/  PDO_DBG_INF_FMT (char*,scalar_t__) ; 
 int /*<<< orphan*/  PDO_DBG_RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mysql_free_result (int /*<<< orphan*/ *) ; 
 scalar_t__ mysql_real_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdo_mysql_error_stmt (TYPE_1__*) ; 
 int /*<<< orphan*/  pdo_mysql_fill_stmt_from_result (TYPE_1__*) ; 
 int /*<<< orphan*/  pdo_mysql_stmt_execute_prepared (TYPE_1__*) ; 

__attribute__((used)) static int pdo_mysql_stmt_execute(pdo_stmt_t *stmt) /* {{{ */
{
	pdo_mysql_stmt *S = (pdo_mysql_stmt*)stmt->driver_data;
	pdo_mysql_db_handle *H = S->H;
	PDO_DBG_ENTER("pdo_mysql_stmt_execute");
	PDO_DBG_INF_FMT("stmt=%p", S->stmt);

	if (S->stmt) {
		PDO_DBG_RETURN(pdo_mysql_stmt_execute_prepared(stmt));
	}

	/* ensure that we free any previous unfetched results */
	if (S->result) {
		mysql_free_result(S->result);
		S->result = NULL;
	}

	if (mysql_real_query(H->server, stmt->active_query_string, stmt->active_query_stringlen) != 0) {
		pdo_mysql_error_stmt(stmt);
		PDO_DBG_RETURN(0);
	}

	PDO_DBG_RETURN(pdo_mysql_fill_stmt_from_result(stmt));
}