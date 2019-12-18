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
typedef  int /*<<< orphan*/  zval ;
typedef  int zend_ulong ;
struct pdo_bound_param_data {int /*<<< orphan*/  parameter; scalar_t__ driver_data; } ;
typedef  int /*<<< orphan*/  php_stream ;
struct TYPE_6__ {int row_count; int column_count; scalar_t__ executed; scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_7__ {char* convbuf; scalar_t__ going_long; int /*<<< orphan*/  cols; int /*<<< orphan*/  stmt; } ;
typedef  TYPE_2__ pdo_odbc_stmt ;
struct TYPE_8__ {int /*<<< orphan*/  is_unicode; } ;
typedef  TYPE_3__ pdo_odbc_param ;
typedef  int /*<<< orphan*/  pdo_odbc_column ;
typedef  scalar_t__ SQLSMALLINT ;
typedef  int /*<<< orphan*/  SQLPOINTER ;
typedef  int SQLLEN ;
typedef  int RETCODE ;

/* Variables and functions */
 scalar_t__ IS_RESOURCE ; 
#define  PDO_ODBC_CONV_FAIL 133 
#define  PDO_ODBC_CONV_NOT_REQUIRED 132 
#define  PDO_ODBC_CONV_OK 131 
 int /*<<< orphan*/  SQLCloseCursor (int /*<<< orphan*/ ) ; 
 int SQLExecute (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SQLNumResultCols (int /*<<< orphan*/ ,scalar_t__*) ; 
 int SQLParamData (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SQLPutData (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  SQLRowCount (int /*<<< orphan*/ ,int*) ; 
 int SQL_NEED_DATA ; 
#define  SQL_NO_DATA_FOUND 130 
#define  SQL_SUCCESS 129 
#define  SQL_SUCCESS_WITH_INFO 128 
 scalar_t__ Z_ISREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Z_REFVAL (int /*<<< orphan*/ ) ; 
 int Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 char* Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  convert_to_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecalloc (scalar_t__,int) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* emalloc (int) ; 
 int /*<<< orphan*/  pdo_odbc_stmt_error (char*) ; 
 int pdo_odbc_utf82ucs2 (TYPE_1__*,int /*<<< orphan*/ ,char*,int,int*) ; 
 int /*<<< orphan*/  php_stream_from_zval_no_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int php_stream_read (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int odbc_stmt_execute(pdo_stmt_t *stmt)
{
	RETCODE rc;
	pdo_odbc_stmt *S = (pdo_odbc_stmt*)stmt->driver_data;
	char *buf = NULL;
	SQLLEN row_count = -1;

	if (stmt->executed) {
		SQLCloseCursor(S->stmt);
	}

	rc = SQLExecute(S->stmt);

	while (rc == SQL_NEED_DATA) {
		struct pdo_bound_param_data *param;

		rc = SQLParamData(S->stmt, (SQLPOINTER*)&param);
		if (rc == SQL_NEED_DATA) {
			php_stream *stm;
			int len;
			pdo_odbc_param *P;
			zval *parameter;

			P = (pdo_odbc_param*)param->driver_data;
			if (Z_ISREF(param->parameter)) {
				parameter = Z_REFVAL(param->parameter);
			} else {
				parameter = &param->parameter;
			}
			if (Z_TYPE_P(parameter) != IS_RESOURCE) {
				/* they passed in a string */
				zend_ulong ulen;
				convert_to_string(parameter);

				switch (pdo_odbc_utf82ucs2(stmt, P->is_unicode,
							Z_STRVAL_P(parameter),
							Z_STRLEN_P(parameter),
							&ulen)) {
					case PDO_ODBC_CONV_NOT_REQUIRED:
						SQLPutData(S->stmt, Z_STRVAL_P(parameter),
							Z_STRLEN_P(parameter));
						break;
					case PDO_ODBC_CONV_OK:
						SQLPutData(S->stmt, S->convbuf, ulen);
						break;
					case PDO_ODBC_CONV_FAIL:
						pdo_odbc_stmt_error("error converting input string");
						SQLCloseCursor(S->stmt);
						if (buf) {
							efree(buf);
						}
						return 0;
				}
				continue;
			}

			/* we assume that LOBs are binary and don't need charset
			 * conversion */

			php_stream_from_zval_no_verify(stm, parameter);
			if (!stm) {
				/* shouldn't happen either */
				pdo_odbc_stmt_error("input LOB is no longer a stream");
				SQLCloseCursor(S->stmt);
				if (buf) {
					efree(buf);
				}
				return 0;
			}

			/* now suck data from the stream and stick it into the database */
			if (buf == NULL) {
				buf = emalloc(8192);
			}

			do {
				len = php_stream_read(stm, buf, 8192);
				if (len == 0) {
					break;
				}
				SQLPutData(S->stmt, buf, len);
			} while (1);
		}
	}

	if (buf) {
		efree(buf);
	}

	switch (rc) {
		case SQL_SUCCESS:
			break;
		case SQL_NO_DATA_FOUND:
		case SQL_SUCCESS_WITH_INFO:
			pdo_odbc_stmt_error("SQLExecute");
			break;

		default:
			pdo_odbc_stmt_error("SQLExecute");
			return 0;
	}

	SQLRowCount(S->stmt, &row_count);
	stmt->row_count = row_count;

	if (!stmt->executed) {
		/* do first-time-only definition of bind/mapping stuff */
		SQLSMALLINT colcount;

		/* how many columns do we have ? */
		SQLNumResultCols(S->stmt, &colcount);

		stmt->column_count = (int)colcount;
		S->cols = ecalloc(colcount, sizeof(pdo_odbc_column));
		S->going_long = 0;
	}

	return 1;
}