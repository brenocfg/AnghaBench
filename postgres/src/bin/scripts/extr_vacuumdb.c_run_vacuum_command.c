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
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  PQdb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 int PQsendQuery (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  pg_log_error (char*,char const*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static void
run_vacuum_command(PGconn *conn, const char *sql, bool echo,
				   const char *table)
{
	bool		status;

	if (echo)
		printf("%s\n", sql);

	status = PQsendQuery(conn, sql) == 1;

	if (!status)
	{
		if (table)
			pg_log_error("vacuuming of table \"%s\" in database \"%s\" failed: %s",
						 table, PQdb(conn), PQerrorMessage(conn));
		else
			pg_log_error("vacuuming of database \"%s\" failed: %s",
						 PQdb(conn), PQerrorMessage(conn));
	}
}