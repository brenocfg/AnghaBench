#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  row_count; scalar_t__ executed; scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_stmt_t ;
struct TYPE_9__ {int done; int pre_fetched; int /*<<< orphan*/  stmt; TYPE_1__* H; } ;
typedef  TYPE_3__ pdo_sqlite_stmt ;
struct TYPE_7__ {int /*<<< orphan*/  db; } ;

/* Variables and functions */
#define  SQLITE_BUSY 132 
#define  SQLITE_DONE 131 
#define  SQLITE_ERROR 130 
#define  SQLITE_MISUSE 129 
#define  SQLITE_ROW 128 
 int /*<<< orphan*/  pdo_sqlite_error_stmt (TYPE_2__*) ; 
 int /*<<< orphan*/  pdo_sqlite_stmt_set_column_count (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_changes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_column_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_data_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ ) ; 
 int sqlite3_step (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pdo_sqlite_stmt_execute(pdo_stmt_t *stmt)
{
	pdo_sqlite_stmt *S = (pdo_sqlite_stmt*)stmt->driver_data;

	if (stmt->executed && !S->done) {
		sqlite3_reset(S->stmt);
	}

	S->done = 0;
	switch (sqlite3_step(S->stmt)) {
		case SQLITE_ROW:
			S->pre_fetched = 1;
			pdo_sqlite_stmt_set_column_count(stmt, sqlite3_data_count(S->stmt));
			return 1;

		case SQLITE_DONE:
			pdo_sqlite_stmt_set_column_count(stmt, sqlite3_column_count(S->stmt));
			stmt->row_count = sqlite3_changes(S->H->db);
			sqlite3_reset(S->stmt);
			S->done = 1;
			return 1;

		case SQLITE_ERROR:
			sqlite3_reset(S->stmt);
		case SQLITE_MISUSE:
		case SQLITE_BUSY:
		default:
			pdo_sqlite_error_stmt(stmt);
			return 0;
	}
}