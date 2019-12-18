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
typedef  int /*<<< orphan*/  zend_long ;
struct TYPE_6__ {scalar_t__ errcode; } ;
struct TYPE_7__ {int /*<<< orphan*/  server; TYPE_1__ einfo; } ;
typedef  TYPE_2__ pdo_mysql_db_handle ;
struct TYPE_8__ {scalar_t__ driver_data; } ;
typedef  TYPE_3__ pdo_dbh_t ;
typedef  scalar_t__ my_ulonglong ;
typedef  int /*<<< orphan*/  MYSQL_RES ;

/* Variables and functions */
 int /*<<< orphan*/  PDO_DBG_ENTER (char*) ; 
 int /*<<< orphan*/  PDO_DBG_INF_FMT (char*,...) ; 
 int /*<<< orphan*/  PDO_DBG_RETURN (int) ; 
 scalar_t__ mysql_affected_rows (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mysql_free_result (int /*<<< orphan*/ *) ; 
 scalar_t__ mysql_more_results (int /*<<< orphan*/ ) ; 
 scalar_t__ mysql_next_result (int /*<<< orphan*/ ) ; 
 scalar_t__ mysql_real_query (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/ * mysql_store_result (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdo_mysql_error (TYPE_3__*) ; 

__attribute__((used)) static zend_long mysql_handle_doer(pdo_dbh_t *dbh, const char *sql, size_t sql_len)
{
	pdo_mysql_db_handle *H = (pdo_mysql_db_handle *)dbh->driver_data;
	PDO_DBG_ENTER("mysql_handle_doer");
	PDO_DBG_INF_FMT("dbh=%p", dbh);
	PDO_DBG_INF_FMT("sql=%.*s", (int)sql_len, sql);

	if (mysql_real_query(H->server, sql, sql_len)) {
		pdo_mysql_error(dbh);
		PDO_DBG_RETURN(-1);
	} else {
		my_ulonglong c = mysql_affected_rows(H->server);
		if (c == (my_ulonglong) -1) {
			pdo_mysql_error(dbh);
			PDO_DBG_RETURN(H->einfo.errcode ? -1 : 0);
		} else {

			/* MULTI_QUERY support - eat up all unfetched result sets */
			MYSQL_RES* result;
			while (mysql_more_results(H->server)) {
				if (mysql_next_result(H->server)) {
					PDO_DBG_RETURN(1);
				}
				result = mysql_store_result(H->server);
				if (result) {
					mysql_free_result(result);
				}
			}
			PDO_DBG_RETURN((int)c);
		}
	}
}