#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_11__ {int supports_placeholders; int /*<<< orphan*/ * methods; TYPE_3__* driver_data; } ;
typedef  TYPE_2__ pdo_stmt_t ;
struct TYPE_12__ {int /*<<< orphan*/  stmt; TYPE_4__* H; } ;
typedef  TYPE_3__ pdo_sqlite_stmt ;
struct TYPE_10__ {int /*<<< orphan*/  errcode; } ;
struct TYPE_13__ {int /*<<< orphan*/  db; TYPE_1__ einfo; } ;
typedef  TYPE_4__ pdo_sqlite_db_handle ;
struct TYPE_14__ {scalar_t__ driver_data; } ;
typedef  TYPE_5__ pdo_dbh_t ;

/* Variables and functions */
 int /*<<< orphan*/  PDO_ATTR_CURSOR ; 
 scalar_t__ PDO_CURSOR_FWDONLY ; 
 int PDO_PLACEHOLDER_NAMED ; 
 int PDO_PLACEHOLDER_POSITIONAL ; 
 int /*<<< orphan*/  SQLITE_ERROR ; 
 int SQLITE_OK ; 
 TYPE_3__* ecalloc (int,int) ; 
 scalar_t__ pdo_attr_lval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pdo_sqlite_error (TYPE_5__*) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  sqlite_stmt_methods ; 

__attribute__((used)) static int sqlite_handle_preparer(pdo_dbh_t *dbh, const char *sql, size_t sql_len, pdo_stmt_t *stmt, zval *driver_options)
{
	pdo_sqlite_db_handle *H = (pdo_sqlite_db_handle *)dbh->driver_data;
	pdo_sqlite_stmt *S = ecalloc(1, sizeof(pdo_sqlite_stmt));
	int i;
	const char *tail;

	S->H = H;
	stmt->driver_data = S;
	stmt->methods = &sqlite_stmt_methods;
	stmt->supports_placeholders = PDO_PLACEHOLDER_POSITIONAL|PDO_PLACEHOLDER_NAMED;

	if (PDO_CURSOR_FWDONLY != pdo_attr_lval(driver_options, PDO_ATTR_CURSOR, PDO_CURSOR_FWDONLY)) {
		H->einfo.errcode = SQLITE_ERROR;
		pdo_sqlite_error(dbh);
		return 0;
	}

	i = sqlite3_prepare_v2(H->db, sql, sql_len, &S->stmt, &tail);
	if (i == SQLITE_OK) {
		return 1;
	}

	pdo_sqlite_error(dbh);

	return 0;
}