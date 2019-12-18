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
struct db_stmt_mysql {int must_execute_again; int /*<<< orphan*/ * param_bind; int /*<<< orphan*/ * result_bind; TYPE_1__ base; int /*<<< orphan*/  stmt; } ;
struct db_stmt {int dummy; } ;
struct db_mysql {int /*<<< orphan*/  con; } ;
struct db {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  db_stmt_bind_mysql ; 
 int /*<<< orphan*/  db_stmt_finalize_mysql ; 
 int /*<<< orphan*/  db_stmt_step_mysql ; 
 int /*<<< orphan*/  free (struct db_stmt_mysql*) ; 
 struct db_stmt_mysql* malloc (int) ; 
 int /*<<< orphan*/  mysql_stmt_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mysql_stmt_init (int /*<<< orphan*/ ) ; 
 scalar_t__ mysql_stmt_prepare (int /*<<< orphan*/ ,char const*,size_t const) ; 

__attribute__((used)) static struct db_stmt *db_prepare_mysql(const struct db *db, const char *sql,
        const size_t sql_len)
{
    const struct db_mysql *db_mysql = (const struct db_mysql *)db;
    struct db_stmt_mysql *stmt_mysql = malloc(sizeof(*stmt_mysql));

    if (!stmt_mysql)
        return NULL;

    stmt_mysql->stmt = mysql_stmt_init(db_mysql->con);
    if (!stmt_mysql->stmt) {
        free(stmt_mysql);
        return NULL;
    }

    if (mysql_stmt_prepare(stmt_mysql->stmt, sql, sql_len)) {
        mysql_stmt_close(stmt_mysql->stmt);
        free(stmt_mysql);
        return NULL;
    }

    stmt_mysql->base.bind = db_stmt_bind_mysql;
    stmt_mysql->base.step = db_stmt_step_mysql;
    stmt_mysql->base.finalize = db_stmt_finalize_mysql;
    stmt_mysql->result_bind = NULL;
    stmt_mysql->param_bind = NULL;
    stmt_mysql->must_execute_again = true;

    return (struct db_stmt*)stmt_mysql;
}