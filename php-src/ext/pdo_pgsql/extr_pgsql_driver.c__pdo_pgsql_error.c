#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  error_code; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_8__ {int errcode; char const* file; int line; int /*<<< orphan*/ * errmsg; } ;
typedef  TYPE_2__ pdo_pgsql_error_info ;
struct TYPE_9__ {int /*<<< orphan*/  server; TYPE_2__ einfo; } ;
typedef  TYPE_3__ pdo_pgsql_db_handle ;
typedef  int /*<<< orphan*/  pdo_error_type ;
struct TYPE_10__ {int /*<<< orphan*/  methods; int /*<<< orphan*/  is_persistent; int /*<<< orphan*/  error_code; scalar_t__ driver_data; } ;
typedef  TYPE_4__ pdo_dbh_t ;

/* Variables and functions */
 char* PQerrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _pdo_pgsql_trim_message (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * estrdup (char const*) ; 
 int /*<<< orphan*/  pefree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_pdo_get_exception () ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  zend_throw_exception_ex (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int _pdo_pgsql_error(pdo_dbh_t *dbh, pdo_stmt_t *stmt, int errcode, const char *sqlstate, const char *msg, const char *file, int line) /* {{{ */
{
	pdo_pgsql_db_handle *H = (pdo_pgsql_db_handle *)dbh->driver_data;
	pdo_error_type *pdo_err = stmt ? &stmt->error_code : &dbh->error_code;
	pdo_pgsql_error_info *einfo = &H->einfo;
	char *errmsg = PQerrorMessage(H->server);

	einfo->errcode = errcode;
	einfo->file = file;
	einfo->line = line;

	if (einfo->errmsg) {
		pefree(einfo->errmsg, dbh->is_persistent);
		einfo->errmsg = NULL;
	}

	if (sqlstate == NULL || strlen(sqlstate) >= sizeof(pdo_error_type)) {
		strcpy(*pdo_err, "HY000");
	}
	else {
		strcpy(*pdo_err, sqlstate);
	}

	if (msg) {
		einfo->errmsg = estrdup(msg);
	}
	else if (errmsg) {
		einfo->errmsg = _pdo_pgsql_trim_message(errmsg, dbh->is_persistent);
	}

	if (!dbh->methods) {
		zend_throw_exception_ex(php_pdo_get_exception(), einfo->errcode, "SQLSTATE[%s] [%d] %s",
				*pdo_err, einfo->errcode, einfo->errmsg);
	}

	return errcode;
}