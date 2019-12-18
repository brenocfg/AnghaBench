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
typedef  int ub4 ;
typedef  int /*<<< orphan*/  tmp_buf ;
typedef  char text ;
typedef  int sword ;
struct TYPE_8__ {char* error_code; scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_10__ {char* errmsg; int errcode; char const* file; int line; } ;
struct TYPE_9__ {TYPE_3__ einfo; } ;
typedef  TYPE_2__ pdo_oci_stmt ;
typedef  TYPE_3__ pdo_oci_error_info ;
struct TYPE_11__ {TYPE_3__ einfo; int /*<<< orphan*/  attached; } ;
typedef  TYPE_4__ pdo_oci_db_handle ;
typedef  char* pdo_error_type ;
struct TYPE_12__ {char* error_code; int is_closed; int /*<<< orphan*/  methods; int /*<<< orphan*/  is_persistent; scalar_t__ driver_data; } ;
typedef  TYPE_5__ pdo_dbh_t ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  int /*<<< orphan*/  OCIError ;

/* Variables and functions */
 int /*<<< orphan*/  OCIErrorGet (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*,char*,int,int /*<<< orphan*/ ) ; 
#define  OCI_CONTINUE 135 
#define  OCI_ERROR 134 
 int /*<<< orphan*/  OCI_HTYPE_ERROR ; 
#define  OCI_INVALID_HANDLE 133 
#define  OCI_NEED_DATA 132 
#define  OCI_NO_DATA 131 
#define  OCI_STILL_EXECUTING 130 
#define  OCI_SUCCESS 129 
#define  OCI_SUCCESS_WITH_INFO 128 
 int /*<<< orphan*/  pefree (char*,int /*<<< orphan*/ ) ; 
 char* pestrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_pdo_get_exception () ; 
 int /*<<< orphan*/  slprintf (char*,int,char*,char*,char const*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  zend_bailout () ; 
 int /*<<< orphan*/  zend_throw_exception_ex (int /*<<< orphan*/ ,int,char*,char*,char*) ; 

ub4 _oci_error(OCIError *err, pdo_dbh_t *dbh, pdo_stmt_t *stmt, char *what, sword status, int isinit, const char *file, int line) /* {{{ */
{
	text errbuf[1024] = "<<Unknown>>";
	char tmp_buf[2048];
	pdo_oci_db_handle *H = (pdo_oci_db_handle *)dbh->driver_data;
	pdo_oci_error_info *einfo;
	pdo_oci_stmt *S = NULL;
	pdo_error_type *pdo_err = &dbh->error_code;

	if (stmt) {
		S = (pdo_oci_stmt*)stmt->driver_data;
		einfo = &S->einfo;
		pdo_err = &stmt->error_code;
	}
	else {
		einfo = &H->einfo;
	}

	if (einfo->errmsg) {
		pefree(einfo->errmsg, dbh->is_persistent);
	}

	einfo->errmsg = NULL;
	einfo->errcode = 0;
	einfo->file = file;
	einfo->line = line;

	if (isinit) { /* Initialization error */
		strcpy(*pdo_err, "HY000");
		slprintf(tmp_buf, sizeof(tmp_buf), "%s (%s:%d)", what, file, line);
		einfo->errmsg = pestrdup(tmp_buf, dbh->is_persistent);
	}
	else {
		switch (status) {
			case OCI_SUCCESS:
				strcpy(*pdo_err, "00000");
				break;
			case OCI_ERROR:
				OCIErrorGet(err, (ub4)1, NULL, &einfo->errcode, errbuf, (ub4)sizeof(errbuf), OCI_HTYPE_ERROR);
				slprintf(tmp_buf, sizeof(tmp_buf), "%s: %s (%s:%d)", what, errbuf, file, line);
				einfo->errmsg = pestrdup(tmp_buf, dbh->is_persistent);
				break;
			case OCI_SUCCESS_WITH_INFO:
				OCIErrorGet(err, (ub4)1, NULL, &einfo->errcode, errbuf, (ub4)sizeof(errbuf), OCI_HTYPE_ERROR);
				slprintf(tmp_buf, sizeof(tmp_buf), "%s: OCI_SUCCESS_WITH_INFO: %s (%s:%d)", what, errbuf, file, line);
				einfo->errmsg = pestrdup(tmp_buf, dbh->is_persistent);
				break;
			case OCI_NEED_DATA:
				slprintf(tmp_buf, sizeof(tmp_buf), "%s: OCI_NEED_DATA (%s:%d)", what, file, line);
				einfo->errmsg = pestrdup(tmp_buf, dbh->is_persistent);
				break;
			case OCI_NO_DATA:
				slprintf(tmp_buf, sizeof(tmp_buf), "%s: OCI_NO_DATA (%s:%d)", what, file, line);
				einfo->errmsg = pestrdup(tmp_buf, dbh->is_persistent);
				break;
			case OCI_INVALID_HANDLE:
				slprintf(tmp_buf, sizeof(tmp_buf), "%s: OCI_INVALID_HANDLE (%s:%d)", what, file, line);
				einfo->errmsg = pestrdup(tmp_buf, dbh->is_persistent);
				break;
			case OCI_STILL_EXECUTING:
				slprintf(tmp_buf, sizeof(tmp_buf), "%s: OCI_STILL_EXECUTING (%s:%d)", what, file, line);
				einfo->errmsg = pestrdup(tmp_buf, dbh->is_persistent);
				break;
			case OCI_CONTINUE:
				slprintf(tmp_buf, sizeof(tmp_buf), "%s: OCI_CONTINUE (%s:%d)", what, file, line);
				einfo->errmsg = pestrdup(tmp_buf, dbh->is_persistent);
				break;
		}

		if (einfo->errcode) {
			switch (einfo->errcode) {
				case 1013:	/* user requested cancel of current operation */
					zend_bailout();
					break;

				case 12154:	/* ORA-12154: TNS:could not resolve service name */
					strcpy(*pdo_err, "42S02");
					break;

				case	22:	/* ORA-00022: invalid session id */
				case   378:
				case   602:
				case   603:
				case   604:
				case   609:
				case  1012:	/* ORA-01012: */
				case  1033:
				case  1041:
				case  1043:
				case  1089:
				case  1090:
				case  1092:
				case  3113:	/* ORA-03133: end of file on communication channel */
				case  3114:
				case  3122:
				case  3135:
				case 12153:
				case 27146:
				case 28511:
					/* consider the connection closed */
					dbh->is_closed = 1;
					H->attached = 0;
					strcpy(*pdo_err, "01002"); /* FIXME */
					break;

				default:
					strcpy(*pdo_err, "HY000");
			}
		}

		if (stmt) {
			/* always propagate the error code back up to the dbh,
			 * so that we can catch the error information when execute
			 * is called via query.  See Bug #33707 */
			if (H->einfo.errmsg) {
				pefree(H->einfo.errmsg, dbh->is_persistent);
			}
			H->einfo = *einfo;
			H->einfo.errmsg = einfo->errmsg ? pestrdup(einfo->errmsg, dbh->is_persistent) : NULL;
			strcpy(dbh->error_code, stmt->error_code);
		}
	}

	/* little mini hack so that we can use this code from the dbh ctor */
	if (!dbh->methods) {
		zend_throw_exception_ex(php_pdo_get_exception(), einfo->errcode, "SQLSTATE[%s]: %s", *pdo_err, einfo->errmsg);
	}

	return einfo->errcode;
}