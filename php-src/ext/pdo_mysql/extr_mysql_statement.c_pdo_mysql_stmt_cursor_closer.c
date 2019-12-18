#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_stmt_t ;
struct TYPE_7__ {TYPE_1__* H; scalar_t__ stmt; int /*<<< orphan*/ * result; } ;
typedef  TYPE_3__ pdo_mysql_stmt ;
struct TYPE_5__ {int /*<<< orphan*/  server; } ;
typedef  int /*<<< orphan*/  MYSQL_RES ;

/* Variables and functions */
 int /*<<< orphan*/  PDO_DBG_ENTER (char*) ; 
 int /*<<< orphan*/  PDO_DBG_INF_FMT (char*,scalar_t__) ; 
 int /*<<< orphan*/  PDO_DBG_RETURN (int) ; 
 int /*<<< orphan*/  mysql_free_result (int /*<<< orphan*/ *) ; 
 scalar_t__ mysql_more_results (int /*<<< orphan*/ ) ; 
 scalar_t__ mysql_next_result (int /*<<< orphan*/ ) ; 
 int mysql_stmt_free_result (scalar_t__) ; 
 int /*<<< orphan*/ * mysql_store_result (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pdo_mysql_stmt_cursor_closer(pdo_stmt_t *stmt) /* {{{ */
{
	pdo_mysql_stmt *S = (pdo_mysql_stmt*)stmt->driver_data;

	PDO_DBG_ENTER("pdo_mysql_stmt_cursor_closer");
	PDO_DBG_INF_FMT("stmt=%p", S->stmt);
	if (S->result) {
		mysql_free_result(S->result);
		S->result = NULL;
	}
	if (S->stmt) {
		int retval;
		retval = mysql_stmt_free_result(S->stmt);
		PDO_DBG_RETURN(retval ? 0 : 1);
	}

	while (mysql_more_results(S->H->server)) {
		MYSQL_RES *res;
		if (mysql_next_result(S->H->server) != 0) {
			break;
		}
		res = mysql_store_result(S->H->server);
		if (res) {
			mysql_free_result(res);
		}
	}
	PDO_DBG_RETURN(1);
}