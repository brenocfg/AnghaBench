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
struct TYPE_5__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ pdo_sqlite_db_handle ;
struct TYPE_6__ {scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_dbh_t ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  pdo_sqlite_error (TYPE_2__*) ; 
 scalar_t__ sqlite3_exec (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 

__attribute__((used)) static int sqlite_handle_begin(pdo_dbh_t *dbh)
{
	pdo_sqlite_db_handle *H = (pdo_sqlite_db_handle *)dbh->driver_data;
	char *errmsg = NULL;

	if (sqlite3_exec(H->db, "BEGIN", NULL, NULL, &errmsg) != SQLITE_OK) {
		pdo_sqlite_error(dbh);
		if (errmsg)
			sqlite3_free(errmsg);
		return 0;
	}
	return 1;
}