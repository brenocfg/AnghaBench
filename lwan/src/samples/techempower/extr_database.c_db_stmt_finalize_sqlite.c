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
struct db_stmt_sqlite {int /*<<< orphan*/  sqlite; } ;
struct db_stmt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct db_stmt_sqlite*) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void db_stmt_finalize_sqlite(struct db_stmt *stmt)
{
    struct db_stmt_sqlite *stmt_sqlite = (struct db_stmt_sqlite *)stmt;

    sqlite3_finalize(stmt_sqlite->sqlite);
    free(stmt_sqlite);
}