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
struct db_stmt_mysql {int must_execute_again; int /*<<< orphan*/  stmt; TYPE_2__* result_bind; void* param_bind; } ;
struct db_stmt {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  i; int /*<<< orphan*/ * s; } ;
struct db_row {char kind; int /*<<< orphan*/  buffer_length; TYPE_1__ u; } ;
struct TYPE_6__ {int is_null; int /*<<< orphan*/  buffer_length; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  buffer_type; } ;
typedef  TYPE_2__ MYSQL_BIND ;

/* Variables and functions */
 int /*<<< orphan*/  MYSQL_TYPE_LONG ; 
 int /*<<< orphan*/  MYSQL_TYPE_STRING ; 
 void* calloc (size_t,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ mysql_stmt_bind_result (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ mysql_stmt_execute (int /*<<< orphan*/ ) ; 
 scalar_t__ mysql_stmt_fetch (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool db_stmt_step_mysql(const struct db_stmt *stmt, struct db_row *row)
{
    struct db_stmt_mysql *stmt_mysql = (struct db_stmt_mysql *)stmt;

    if (stmt_mysql->must_execute_again) {
        stmt_mysql->must_execute_again = false;
        if (mysql_stmt_execute(stmt_mysql->stmt))
            return false;
    }

    if (!stmt_mysql->result_bind) {
        size_t n_rows = 0;
        for (struct db_row *r = row; r->kind != '\0'; r++)
            n_rows++;

        if (!n_rows)
            return false;

        stmt_mysql->result_bind = calloc(n_rows, sizeof(*stmt_mysql->result_bind));
        if (!stmt_mysql->result_bind)
            return false;

        stmt_mysql->param_bind = calloc(n_rows, sizeof(*stmt_mysql->param_bind));
        if (!stmt_mysql->param_bind) {
            free(stmt_mysql->result_bind);
            return false;
        }

        MYSQL_BIND *result = stmt_mysql->result_bind;
        for (size_t r = 0; r < n_rows; r++) {
            if (row[r].kind == 's') {
                result[r].buffer_type = MYSQL_TYPE_STRING;
                result[r].buffer = row[r].u.s;
            } else if (row[r].kind == 'i') {
                result[r].buffer_type = MYSQL_TYPE_LONG;
                result[r].buffer = &row[r].u.i;
            } else {
                return false;
            }

            result[r].is_null = false;
            result[r].buffer_length = row[r].buffer_length;
        }

        if (mysql_stmt_bind_result(stmt_mysql->stmt, result))
            return false;
    }

    return mysql_stmt_fetch(stmt_mysql->stmt) == 0;
}