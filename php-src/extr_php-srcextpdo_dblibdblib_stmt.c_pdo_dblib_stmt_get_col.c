#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int zend_ulong ;
struct TYPE_8__ {scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_9__ {TYPE_3__* H; } ;
typedef  TYPE_2__ pdo_dblib_stmt ;
struct TYPE_10__ {int /*<<< orphan*/  stringify_uniqueidentifier; int /*<<< orphan*/ * link; } ;
typedef  TYPE_3__ pdo_dblib_db_handle ;
struct TYPE_11__ {int /*<<< orphan*/  datesecond; int /*<<< orphan*/  dateminute; int /*<<< orphan*/  datehour; int /*<<< orphan*/  datedmonth; int /*<<< orphan*/  datemonth; int /*<<< orphan*/  dateyear; } ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  scalar_t__ DBTINYINT ;
typedef  scalar_t__ DBSMALLINT ;
typedef  scalar_t__ DBINT ;
typedef  int /*<<< orphan*/  DBFLT8 ;
typedef  int /*<<< orphan*/  DBFLT4 ;
typedef  int /*<<< orphan*/  DBDATETIME ;
typedef  TYPE_4__ DBDATEREC ;
typedef  int /*<<< orphan*/  DBCHAR ;
typedef  scalar_t__ DBBIGINT ;

/* Variables and functions */
#define  SQLBINARY 148 
#define  SQLBIT 147 
#define  SQLCHAR 146 
#define  SQLDATETIM4 145 
#define  SQLDATETIME 144 
#define  SQLDECIMAL 143 
#define  SQLFLT4 142 
#define  SQLFLT8 141 
#define  SQLIMAGE 140 
#define  SQLINT1 139 
#define  SQLINT2 138 
#define  SQLINT4 137 
#define  SQLINT8 136 
#define  SQLMONEY 135 
#define  SQLMONEY4 134 
#define  SQLMONEYN 133 
#define  SQLNUMERIC 132 
#define  SQLTEXT 131 
#define  SQLUNIQUE 130 
#define  SQLVARBINARY 129 
#define  SQLVARCHAR 128 
 int /*<<< orphan*/  ZVAL_DOUBLE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int dbcoltype (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dbconvert (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *,scalar_t__,int const,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * dbdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dbdatecrack (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ dbdatlen (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dbwillconvert (int,int const) ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * emalloc (int) ; 
 scalar_t__ pdo_dblib_stmt_should_stringify_col (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pdo_dblib_stmt_stringify_col (int,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  php_strtoupper (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * safe_emalloc (scalar_t__,int,int) ; 
 size_t spprintf (int /*<<< orphan*/ **,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pdo_dblib_stmt_get_col(pdo_stmt_t *stmt, int colno, char **ptr,
	 zend_ulong *len, int *caller_frees)
{

	pdo_dblib_stmt *S = (pdo_dblib_stmt*)stmt->driver_data;
	pdo_dblib_db_handle *H = S->H;

	int coltype;
	LPBYTE data;
	DBCHAR *tmp_data;
	DBINT data_len, tmp_data_len;
	zval *zv = NULL;

	coltype = dbcoltype(H->link, colno+1);
	data = dbdata(H->link, colno+1);
	data_len = dbdatlen(H->link, colno+1);

	if (data_len != 0 || data != NULL) {
		if (pdo_dblib_stmt_should_stringify_col(stmt, coltype) && dbwillconvert(coltype, SQLCHAR)) {
			pdo_dblib_stmt_stringify_col(coltype, data, data_len, &zv);
		}

		if (!zv) {
			switch (coltype) {
				case SQLCHAR:
				case SQLVARCHAR:
				case SQLTEXT: {
#if ilia_0
					while (data_len>0 && data[data_len-1] == ' ') { /* nuke trailing whitespace */
						data_len--;
					}
#endif
				}
				case SQLVARBINARY:
				case SQLBINARY:
				case SQLIMAGE: {
					zv = emalloc(sizeof(zval));
					ZVAL_STRINGL(zv, (DBCHAR *) data, data_len);

					break;
				}
#ifdef SQLMSDATETIME2
				case SQLMSDATETIME2:
#endif
				case SQLDATETIME:
				case SQLDATETIM4: {
					size_t dl;
					DBDATEREC di;
					DBDATEREC dt;

					dbconvert(H->link, coltype, data, -1, SQLDATETIME, (LPBYTE) &dt, -1);
					dbdatecrack(H->link, &di, (DBDATETIME *) &dt);

					dl = spprintf(&tmp_data, 20, "%04d-%02d-%02d %02d:%02d:%02d",
#if defined(PHP_DBLIB_IS_MSSQL) || defined(MSDBLIB)
							di.year,     di.month,       di.day,        di.hour,     di.minute,     di.second
#else
							di.dateyear, di.datemonth+1, di.datedmonth, di.datehour, di.dateminute, di.datesecond
#endif
					);

					zv = emalloc(sizeof(zval));
					ZVAL_STRINGL(zv, tmp_data, dl);

					efree(tmp_data);

					break;
				}
				case SQLFLT4: {
					zv = emalloc(sizeof(zval));
					ZVAL_DOUBLE(zv, *(DBFLT4 *) data);

					break;
				}
				case SQLFLT8: {
					zv = emalloc(sizeof(zval));
					ZVAL_DOUBLE(zv, *(DBFLT8 *) data);

					break;
				}
				case SQLINT8: {
					zv = emalloc(sizeof(zval));
					ZVAL_LONG(zv, *(DBBIGINT *) data);

					break;
				}
				case SQLINT4: {
					zv = emalloc(sizeof(zval));
					ZVAL_LONG(zv, *(DBINT *) data);

					break;
				}
				case SQLINT2: {
					zv = emalloc(sizeof(zval));
					ZVAL_LONG(zv, *(DBSMALLINT *) data);

					break;
				}
				case SQLINT1:
				case SQLBIT: {
					zv = emalloc(sizeof(zval));
					ZVAL_LONG(zv, *(DBTINYINT *) data);

					break;
				}
				case SQLDECIMAL:
				case SQLNUMERIC:
				case SQLMONEY:
				case SQLMONEY4:
				case SQLMONEYN: {
					DBFLT8 float_value;
					dbconvert(NULL, coltype, data, 8, SQLFLT8, (LPBYTE) &float_value, -1);

					zv = emalloc(sizeof(zval));
					ZVAL_DOUBLE(zv, float_value);

					break;
				}

				case SQLUNIQUE: {
					if (H->stringify_uniqueidentifier) {
						/* 36-char hex string representation */
						tmp_data_len = 36;
						tmp_data = safe_emalloc(tmp_data_len, sizeof(char), 1);
						data_len = dbconvert(NULL, SQLUNIQUE, data, data_len, SQLCHAR, (LPBYTE) tmp_data, tmp_data_len);
						php_strtoupper(tmp_data, data_len);
						zv = emalloc(sizeof(zval));
						ZVAL_STRINGL(zv, tmp_data, data_len);
						efree(tmp_data);
					} else {
						/* 16-byte binary representation */
						zv = emalloc(sizeof(zval));
						ZVAL_STRINGL(zv, (DBCHAR *) data, 16);
					}
					break;
				}

				default: {
					if (dbwillconvert(coltype, SQLCHAR)) {
						pdo_dblib_stmt_stringify_col(coltype, data, data_len, &zv);
					}

					break;
				}
			}
		}
	}

	if (zv != NULL) {
		*ptr = (char*)zv;
		*len = sizeof(zval);
	} else {
		*ptr = NULL;
		*len = 0;
	}

	*caller_frees = 1;

	return 1;
}