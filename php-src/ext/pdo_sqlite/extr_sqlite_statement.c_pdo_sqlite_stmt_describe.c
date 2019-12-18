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
struct TYPE_7__ {TYPE_1__* columns; scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_stmt_t ;
struct TYPE_8__ {int /*<<< orphan*/  stmt; } ;
typedef  TYPE_3__ pdo_sqlite_stmt ;
struct TYPE_6__ {int maxlen; int /*<<< orphan*/  param_type; scalar_t__ precision; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDO_PARAM_STR ; 
#define  SQLITE3_TEXT 132 
#define  SQLITE_BLOB 131 
#define  SQLITE_FLOAT 130 
#define  SQLITE_INTEGER 129 
#define  SQLITE_NULL 128 
 int /*<<< orphan*/  pdo_sqlite_error_stmt (TYPE_2__*) ; 
 int sqlite3_column_count (int /*<<< orphan*/ ) ; 
 char* sqlite3_column_name (int /*<<< orphan*/ ,int) ; 
 int sqlite3_column_type (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  zend_string_init (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pdo_sqlite_stmt_describe(pdo_stmt_t *stmt, int colno)
{
	pdo_sqlite_stmt *S = (pdo_sqlite_stmt*)stmt->driver_data;
	const char *str;

	if(colno >= sqlite3_column_count(S->stmt)) {
		/* error invalid column */
		pdo_sqlite_error_stmt(stmt);
		return 0;
	}

	str = sqlite3_column_name(S->stmt, colno);
	stmt->columns[colno].name = zend_string_init(str, strlen(str), 0);
	stmt->columns[colno].maxlen = 0xffffffff;
	stmt->columns[colno].precision = 0;

	switch (sqlite3_column_type(S->stmt, colno)) {
		case SQLITE_INTEGER:
		case SQLITE_FLOAT:
		case SQLITE3_TEXT:
		case SQLITE_BLOB:
		case SQLITE_NULL:
		default:
			stmt->columns[colno].param_type = PDO_PARAM_STR;
			break;
	}

	return 1;
}