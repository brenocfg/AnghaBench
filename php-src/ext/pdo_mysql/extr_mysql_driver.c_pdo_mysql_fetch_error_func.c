#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_10__ {scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_12__ {int /*<<< orphan*/  errmsg; scalar_t__ errcode; } ;
struct TYPE_11__ {TYPE_3__ einfo; } ;
typedef  TYPE_2__ pdo_mysql_stmt ;
typedef  TYPE_3__ pdo_mysql_error_info ;
struct TYPE_13__ {TYPE_3__ einfo; } ;
typedef  TYPE_4__ pdo_mysql_db_handle ;
struct TYPE_14__ {scalar_t__ driver_data; } ;
typedef  TYPE_5__ pdo_dbh_t ;

/* Variables and functions */
 int /*<<< orphan*/  PDO_DBG_ENTER (char*) ; 
 int /*<<< orphan*/  PDO_DBG_INF_FMT (char*,TYPE_5__*,TYPE_1__*) ; 
 int /*<<< orphan*/  PDO_DBG_RETURN (int) ; 
 int /*<<< orphan*/  add_next_index_long (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  add_next_index_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pdo_mysql_fetch_error_func(pdo_dbh_t *dbh, pdo_stmt_t *stmt, zval *info)
{
	pdo_mysql_db_handle *H = (pdo_mysql_db_handle *)dbh->driver_data;
	pdo_mysql_error_info *einfo = &H->einfo;

	PDO_DBG_ENTER("pdo_mysql_fetch_error_func");
	PDO_DBG_INF_FMT("dbh=%p stmt=%p", dbh, stmt);
	if (stmt) {
		pdo_mysql_stmt *S = (pdo_mysql_stmt*)stmt->driver_data;
		einfo = &S->einfo;
	} else {
		einfo = &H->einfo;
	}

	if (einfo->errcode) {
		add_next_index_long(info, einfo->errcode);
		add_next_index_string(info, einfo->errmsg);
	}

	PDO_DBG_RETURN(1);
}