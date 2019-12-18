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
struct pdo_column_data {int maxlen; int /*<<< orphan*/  param_type; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {struct pdo_column_data* columns; scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_stmt_t ;
struct TYPE_8__ {int going_long; TYPE_1__* cols; int /*<<< orphan*/  stmt; } ;
typedef  TYPE_3__ pdo_odbc_stmt ;
struct TYPE_6__ {scalar_t__ coltype; int datalen; int is_long; void* data; int /*<<< orphan*/  fetched_len; scalar_t__ is_unicode; int /*<<< orphan*/  colname; } ;
typedef  int /*<<< orphan*/  SWORD ;
typedef  int SQLULEN ;
typedef  int SQLLEN ;
typedef  scalar_t__ RETCODE ;

/* Variables and functions */
 int /*<<< orphan*/  PDO_PARAM_STR ; 
 scalar_t__ SQLBindCol (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ SQLColAttribute (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ SQLDescribeCol (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SQL_C_BINARY ; 
 int /*<<< orphan*/  SQL_C_CHAR ; 
 int /*<<< orphan*/  SQL_DESC_DISPLAY_SIZE ; 
 scalar_t__ SQL_LONGVARBINARY ; 
 scalar_t__ SQL_LONGVARCHAR ; 
 scalar_t__ SQL_SUCCESS ; 
 scalar_t__ SQL_SUCCESS_WITH_INFO ; 
 scalar_t__ SQL_VARBINARY ; 
 scalar_t__ SQL_VARCHAR ; 
 scalar_t__ SQL_WLONGVARCHAR ; 
 scalar_t__ SQL_WVARCHAR ; 
 void* emalloc (int) ; 
 scalar_t__ pdo_odbc_sqltype_is_unicode (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  pdo_odbc_stmt_error (char*) ; 
 int /*<<< orphan*/  zend_string_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int odbc_stmt_describe(pdo_stmt_t *stmt, int colno)
{
	pdo_odbc_stmt *S = (pdo_odbc_stmt*)stmt->driver_data;
	struct pdo_column_data *col = &stmt->columns[colno];
	RETCODE rc;
	SWORD	colnamelen;
	SQLULEN	colsize;
	SQLLEN displaysize;

	rc = SQLDescribeCol(S->stmt, colno+1, S->cols[colno].colname,
			sizeof(S->cols[colno].colname)-1, &colnamelen,
			&S->cols[colno].coltype, &colsize, NULL, NULL);

	/* This fixes a known issue with SQL Server and (max) lengths,
	may affect others as well.  If we are SQL_VARCHAR,
	SQL_VARBINARY, or SQL_WVARCHAR (or any of the long variations)
	and zero is returned from colsize then consider it long */
	if (0 == colsize &&
		(S->cols[colno].coltype == SQL_VARCHAR ||
		 S->cols[colno].coltype == SQL_LONGVARCHAR ||
#ifdef SQL_WVARCHAR
		 S->cols[colno].coltype == SQL_WVARCHAR ||
#endif
#ifdef SQL_WLONGVARCHAR
		 S->cols[colno].coltype == SQL_WLONGVARCHAR ||
#endif
		 S->cols[colno].coltype == SQL_VARBINARY ||
		 S->cols[colno].coltype == SQL_LONGVARBINARY)) {
			 S->going_long = 1;
	}

	if (rc != SQL_SUCCESS) {
		pdo_odbc_stmt_error("SQLDescribeCol");
		if (rc != SQL_SUCCESS_WITH_INFO) {
			return 0;
		}
	}

	rc = SQLColAttribute(S->stmt, colno+1,
			SQL_DESC_DISPLAY_SIZE,
			NULL, 0, NULL, &displaysize);

	if (rc != SQL_SUCCESS) {
		pdo_odbc_stmt_error("SQLColAttribute");
		if (rc != SQL_SUCCESS_WITH_INFO) {
			return 0;
		}
	}
	colsize = displaysize;

	col->maxlen = S->cols[colno].datalen = colsize;
	col->name = zend_string_init(S->cols[colno].colname, colnamelen, 0);
	S->cols[colno].is_unicode = pdo_odbc_sqltype_is_unicode(S, S->cols[colno].coltype);

	/* returning data as a string */
	col->param_type = PDO_PARAM_STR;

	/* tell ODBC to put it straight into our buffer, but only if it
	 * isn't "long" data, and only if we haven't already bound a long
	 * column. */
	if (colsize < 256 && !S->going_long) {
		S->cols[colno].data = emalloc(colsize+1);
		S->cols[colno].is_long = 0;

		rc = SQLBindCol(S->stmt, colno+1,
			S->cols[colno].is_unicode ? SQL_C_BINARY : SQL_C_CHAR,
			S->cols[colno].data,
 			S->cols[colno].datalen+1, &S->cols[colno].fetched_len);

		if (rc != SQL_SUCCESS) {
			pdo_odbc_stmt_error("SQLBindCol");
			return 0;
		}
	} else {
		/* allocate a smaller buffer to keep around for smaller
		 * "long" columns */
		S->cols[colno].data = emalloc(256);
		S->going_long = 1;
		S->cols[colno].is_long = 1;
	}

	return 1;
}