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
struct TYPE_2__ {int /*<<< orphan*/  finalize; int /*<<< orphan*/  step; int /*<<< orphan*/  bind; } ;
struct db_stmt_sqlite {TYPE_1__ base; int /*<<< orphan*/  sqlite; } ;
struct db_stmt {int dummy; } ;
struct db_sqlite {int /*<<< orphan*/  sqlite; } ;
struct db {int dummy; } ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  db_stmt_bind_sqlite ; 
 int /*<<< orphan*/  db_stmt_finalize_sqlite ; 
 int /*<<< orphan*/  db_stmt_step_sqlite ; 
 int /*<<< orphan*/  free (struct db_stmt_sqlite*) ; 
 struct db_stmt_sqlite* malloc (int) ; 
 int sqlite3_prepare (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct db_stmt *db_prepare_sqlite(const struct db *db, const char *sql,
        const size_t sql_len)
{
    const struct db_sqlite *db_sqlite = (const struct db_sqlite *)db;
    struct db_stmt_sqlite *stmt_sqlite = malloc(sizeof(*stmt_sqlite));

    if (!stmt_sqlite)
        return NULL;

    int ret = sqlite3_prepare(db_sqlite->sqlite, sql, (int)sql_len, &stmt_sqlite->sqlite, NULL);
    if (ret != SQLITE_OK) {
        free(stmt_sqlite);
        return NULL;
    }

    stmt_sqlite->base.bind = db_stmt_bind_sqlite;
    stmt_sqlite->base.step = db_stmt_step_sqlite;
    stmt_sqlite->base.finalize = db_stmt_finalize_sqlite;

    return (struct db_stmt *)stmt_sqlite;
}