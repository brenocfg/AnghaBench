#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_long ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3_int64 ;

/* Variables and functions */
#define  SQLITE3_TEXT 132 
#define  SQLITE_BLOB 131 
#define  SQLITE_FLOAT 130 
#define  SQLITE_INTEGER 129 
#define  SQLITE_NULL 128 
 int /*<<< orphan*/  ZEND_LONG_MAX ; 
 int /*<<< orphan*/  ZEND_LONG_MIN ; 
 int /*<<< orphan*/  ZVAL_DOUBLE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_column_blob (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_double (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_int64 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_type (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void sqlite_value_to_zval(sqlite3_stmt *stmt, int column, zval *data) /* {{{ */
{
	sqlite3_int64 val;

	switch (sqlite3_column_type(stmt, column)) {
		case SQLITE_INTEGER:
			val = sqlite3_column_int64(stmt, column);
#if LONG_MAX <= 2147483647
			if (val > ZEND_LONG_MAX || val < ZEND_LONG_MIN) {
				ZVAL_STRINGL(data, (char *)sqlite3_column_text(stmt, column), sqlite3_column_bytes(stmt, column));
			} else {
#endif
				ZVAL_LONG(data, (zend_long) val);
#if LONG_MAX <= 2147483647
			}
#endif
			break;

		case SQLITE_FLOAT:
			ZVAL_DOUBLE(data, sqlite3_column_double(stmt, column));
			break;

		case SQLITE_NULL:
			ZVAL_NULL(data);
			break;

		case SQLITE3_TEXT:
			ZVAL_STRING(data, (char*)sqlite3_column_text(stmt, column));
			break;

		case SQLITE_BLOB:
		default:
			ZVAL_STRINGL(data, (char*)sqlite3_column_blob(stmt, column), sqlite3_column_bytes(stmt, column));
	}
}