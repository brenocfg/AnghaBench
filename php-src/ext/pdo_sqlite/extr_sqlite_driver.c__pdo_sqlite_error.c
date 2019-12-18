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
struct TYPE_8__ {int errcode; char const* file; int line; scalar_t__ errmsg; } ;
typedef  TYPE_2__ pdo_sqlite_error_info ;
struct TYPE_9__ {int /*<<< orphan*/  db; TYPE_2__ einfo; } ;
typedef  TYPE_3__ pdo_sqlite_db_handle ;
typedef  int /*<<< orphan*/  pdo_error_type ;
struct TYPE_10__ {int /*<<< orphan*/  methods; int /*<<< orphan*/  is_persistent; int /*<<< orphan*/  error_code; scalar_t__ driver_data; } ;
typedef  TYPE_4__ pdo_dbh_t ;

/* Variables and functions */
 char* PDO_ERR_NONE ; 
#define  SQLITE_CONSTRAINT 133 
#define  SQLITE_ERROR 132 
#define  SQLITE_INTERRUPT 131 
#define  SQLITE_NOLFS 130 
#define  SQLITE_NOTFOUND 129 
 int SQLITE_OK ; 
#define  SQLITE_TOOBIG 128 
 int /*<<< orphan*/  pefree (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pestrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_pdo_get_exception () ; 
 int sqlite3_errcode (int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zend_throw_exception_ex (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int,scalar_t__) ; 

int _pdo_sqlite_error(pdo_dbh_t *dbh, pdo_stmt_t *stmt, const char *file, int line) /* {{{ */
{
	pdo_sqlite_db_handle *H = (pdo_sqlite_db_handle *)dbh->driver_data;
	pdo_error_type *pdo_err = stmt ? &stmt->error_code : &dbh->error_code;
	pdo_sqlite_error_info *einfo = &H->einfo;

	einfo->errcode = sqlite3_errcode(H->db);
	einfo->file = file;
	einfo->line = line;

	if (einfo->errcode != SQLITE_OK) {
		if (einfo->errmsg) {
			pefree(einfo->errmsg, dbh->is_persistent);
		}
		einfo->errmsg = pestrdup((char*)sqlite3_errmsg(H->db), dbh->is_persistent);
	} else { /* no error */
		strncpy(*pdo_err, PDO_ERR_NONE, sizeof(*pdo_err));
		return 0;
	}
	switch (einfo->errcode) {
		case SQLITE_NOTFOUND:
			strncpy(*pdo_err, "42S02", sizeof(*pdo_err));
			break;

		case SQLITE_INTERRUPT:
			strncpy(*pdo_err, "01002", sizeof(*pdo_err));
			break;

		case SQLITE_NOLFS:
			strncpy(*pdo_err, "HYC00", sizeof(*pdo_err));
			break;

		case SQLITE_TOOBIG:
			strncpy(*pdo_err, "22001", sizeof(*pdo_err));
			break;

		case SQLITE_CONSTRAINT:
			strncpy(*pdo_err, "23000", sizeof(*pdo_err));
			break;

		case SQLITE_ERROR:
		default:
			strncpy(*pdo_err, "HY000", sizeof(*pdo_err));
			break;
	}

	if (!dbh->methods) {
		zend_throw_exception_ex(php_pdo_get_exception(), einfo->errcode, "SQLSTATE[%s] [%d] %s",
				*pdo_err, einfo->errcode, einfo->errmsg);
	}

	return einfo->errcode;
}