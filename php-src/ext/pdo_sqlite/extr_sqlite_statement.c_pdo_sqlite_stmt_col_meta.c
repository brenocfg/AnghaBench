#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  scalar_t__ zend_long ;
struct TYPE_5__ {scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_6__ {int /*<<< orphan*/  stmt; } ;
typedef  TYPE_2__ pdo_sqlite_stmt ;

/* Variables and functions */
 int FAILURE ; 
#define  SQLITE_BLOB 132 
#define  SQLITE_FLOAT 131 
#define  SQLITE_INTEGER 130 
#define  SQLITE_NULL 129 
#define  SQLITE_TEXT 128 
 int SUCCESS ; 
 int /*<<< orphan*/  add_assoc_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  add_assoc_zval (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_next_index_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdo_sqlite_error_stmt (TYPE_1__*) ; 
 char* sqlite3_column_decltype (int /*<<< orphan*/ ,scalar_t__) ; 
 char* sqlite3_column_table_name (int /*<<< orphan*/ ,scalar_t__) ; 
 int sqlite3_column_type (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ sqlite3_data_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pdo_sqlite_stmt_col_meta(pdo_stmt_t *stmt, zend_long colno, zval *return_value)
{
	pdo_sqlite_stmt *S = (pdo_sqlite_stmt*)stmt->driver_data;
	const char *str;
	zval flags;

	if (!S->stmt) {
		return FAILURE;
	}
	if(colno >= sqlite3_data_count(S->stmt)) {
		/* error invalid column */
		pdo_sqlite_error_stmt(stmt);
		return FAILURE;
	}

	array_init(return_value);
	array_init(&flags);

	switch (sqlite3_column_type(S->stmt, colno)) {
		case SQLITE_NULL:
			add_assoc_string(return_value, "native_type", "null");
			break;

		case SQLITE_FLOAT:
			add_assoc_string(return_value, "native_type", "double");
			break;

		case SQLITE_BLOB:
			add_next_index_string(&flags, "blob");
		case SQLITE_TEXT:
			add_assoc_string(return_value, "native_type", "string");
			break;

		case SQLITE_INTEGER:
			add_assoc_string(return_value, "native_type", "integer");
			break;
	}

	str = sqlite3_column_decltype(S->stmt, colno);
	if (str) {
		add_assoc_string(return_value, "sqlite:decl_type", (char *)str);
	}

#ifdef HAVE_SQLITE3_COLUMN_TABLE_NAME
	str = sqlite3_column_table_name(S->stmt, colno);
	if (str) {
		add_assoc_string(return_value, "table", (char *)str);
	}
#endif

	add_assoc_zval(return_value, "flags", &flags);

	return SUCCESS;
}