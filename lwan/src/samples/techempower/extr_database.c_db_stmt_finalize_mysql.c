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
struct db_stmt_mysql {struct db_stmt_mysql* param_bind; struct db_stmt_mysql* result_bind; int /*<<< orphan*/  stmt; } ;
struct db_stmt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct db_stmt_mysql*) ; 
 int /*<<< orphan*/  mysql_stmt_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void db_stmt_finalize_mysql(struct db_stmt *stmt)
{
    struct db_stmt_mysql *stmt_mysql = (struct db_stmt_mysql *)stmt;

    mysql_stmt_close(stmt_mysql->stmt);
    free(stmt_mysql->result_bind);
    free(stmt_mysql->param_bind);
    free(stmt_mysql);
}