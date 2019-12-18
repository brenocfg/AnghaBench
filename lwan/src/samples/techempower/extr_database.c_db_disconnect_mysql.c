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
struct db_mysql {int /*<<< orphan*/  con; } ;
struct db {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct db*) ; 
 int /*<<< orphan*/  mysql_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void db_disconnect_mysql(struct db *db)
{
    struct db_mysql *db_mysql = (struct db_mysql *)db;

    mysql_close(db_mysql->con);
    free(db);
}