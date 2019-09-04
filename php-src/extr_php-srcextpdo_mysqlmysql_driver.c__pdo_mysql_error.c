#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  error_code; scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_10__ {int errcode; char const* file; int line; int /*<<< orphan*/ * errmsg; } ;
struct TYPE_9__ {scalar_t__ stmt; TYPE_3__ einfo; } ;
typedef  TYPE_2__ pdo_mysql_stmt ;
typedef  TYPE_3__ pdo_mysql_error_info ;
struct TYPE_11__ {int /*<<< orphan*/  server; TYPE_3__ einfo; } ;
typedef  TYPE_4__ pdo_mysql_db_handle ;
typedef  int /*<<< orphan*/  pdo_error_type ;
struct TYPE_12__ {int /*<<< orphan*/  methods; int /*<<< orphan*/  is_persistent; int /*<<< orphan*/  error_code; scalar_t__ driver_data; } ;
typedef  TYPE_5__ pdo_dbh_t ;

/* Variables and functions */
 int /*<<< orphan*/  PDO_DBG_ENTER (char*) ; 
 int /*<<< orphan*/  PDO_DBG_INF (char*) ; 
 int /*<<< orphan*/  PDO_DBG_INF_FMT (char*,char const*,int) ; 
 int /*<<< orphan*/  PDO_DBG_RETURN (int) ; 
 int /*<<< orphan*/  PDO_ERR_NONE ; 
 int mysql_errno (int /*<<< orphan*/ ) ; 
 char* mysql_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mysql_sqlstate (int /*<<< orphan*/ ) ; 
 int mysql_stmt_errno (scalar_t__) ; 
 int /*<<< orphan*/  mysql_stmt_sqlstate (scalar_t__) ; 
 int /*<<< orphan*/  pefree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* pestrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_pdo_get_exception () ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_throw_exception_ex (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int _pdo_mysql_error(pdo_dbh_t *dbh, pdo_stmt_t *stmt, const char *file, int line)
{
	pdo_mysql_db_handle *H = (pdo_mysql_db_handle *)dbh->driver_data;
	pdo_error_type *pdo_err;
	pdo_mysql_error_info *einfo;
	pdo_mysql_stmt *S = NULL;

	PDO_DBG_ENTER("_pdo_mysql_error");
	PDO_DBG_INF_FMT("file=%s line=%d", file, line);
	if (stmt) {
		S = (pdo_mysql_stmt*)stmt->driver_data;
		pdo_err = &stmt->error_code;
		einfo   = &S->einfo;
	} else {
		pdo_err = &dbh->error_code;
		einfo   = &H->einfo;
	}

	if (S && S->stmt) {
		einfo->errcode = mysql_stmt_errno(S->stmt);
	} else {
		einfo->errcode = mysql_errno(H->server);
	}

	einfo->file = file;
	einfo->line = line;

	if (einfo->errmsg) {
		pefree(einfo->errmsg, dbh->is_persistent);
		einfo->errmsg = NULL;
	}

	if (einfo->errcode) {
		if (einfo->errcode == 2014) {
			einfo->errmsg = pestrdup(
				"Cannot execute queries while other unbuffered queries are active.  "
				"Consider using PDOStatement::fetchAll().  Alternatively, if your code "
				"is only ever going to run against mysql, you may enable query "
				"buffering by setting the PDO::MYSQL_ATTR_USE_BUFFERED_QUERY attribute.",
				dbh->is_persistent);
		} else if (einfo->errcode == 2057) {
			einfo->errmsg = pestrdup(
				"A stored procedure returning result sets of different size was called. "
				"This is not supported by libmysql",
				dbh->is_persistent);

		} else {
			einfo->errmsg = pestrdup(mysql_error(H->server), dbh->is_persistent);
		}
	} else { /* no error */
		strcpy(*pdo_err, PDO_ERR_NONE);
		PDO_DBG_RETURN(0);
	}

	if (S && S->stmt) {
		strcpy(*pdo_err, mysql_stmt_sqlstate(S->stmt));
	} else {
		strcpy(*pdo_err, mysql_sqlstate(H->server));
	}

	if (!dbh->methods) {
		PDO_DBG_INF("Throwing exception");
		zend_throw_exception_ex(php_pdo_get_exception(), einfo->errcode, "SQLSTATE[%s] [%d] %s",
				*pdo_err, einfo->errcode, einfo->errmsg);
	}

	PDO_DBG_RETURN(einfo->errcode);
}