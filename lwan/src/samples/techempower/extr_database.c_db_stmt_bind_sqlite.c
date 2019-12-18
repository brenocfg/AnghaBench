#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct db_stmt_sqlite {int /*<<< orphan*/  sqlite; } ;
struct db_stmt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i; int /*<<< orphan*/  s; } ;
struct db_row {char kind; TYPE_1__ u; } ;

/* Variables and functions */
 int SQLITE_OK ; 
 int sqlite3_bind_int (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int sqlite3_bind_text (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_clear_bindings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool db_stmt_bind_sqlite(const struct db_stmt *stmt, struct db_row *rows, size_t n_rows)
{
    const struct db_stmt_sqlite *stmt_sqlite = (const struct db_stmt_sqlite *)stmt;
    const struct db_row *rows_1_based = rows - 1;
    int ret;

    sqlite3_reset(stmt_sqlite->sqlite);
    sqlite3_clear_bindings(stmt_sqlite->sqlite);

    for (size_t row = 1; row <= n_rows; row++) {
        const struct db_row *r = &rows_1_based[row];
        if (r->kind == '\0') break;

        if (r->kind == 's') {
            ret = sqlite3_bind_text(stmt_sqlite->sqlite, (int)row, r->u.s, -1, NULL);
            if (ret != SQLITE_OK)
                return false;
        } else if (r->kind == 'i') {
            ret = sqlite3_bind_int(stmt_sqlite->sqlite, (int)row, r->u.i);
            if (ret != SQLITE_OK)
                return false;
        } else {
            return false;
        }
    }

    return true;
}