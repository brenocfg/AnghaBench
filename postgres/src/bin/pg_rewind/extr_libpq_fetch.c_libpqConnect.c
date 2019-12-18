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
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  ALWAYS_SECURE_SEARCH_PATH_SQL ; 
 scalar_t__ CONNECTION_BAD ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQconnectdb (char const*) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQresultErrorMessage (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  pg_fatal (char*,...) ; 
 int /*<<< orphan*/  pg_free (char*) ; 
 int /*<<< orphan*/  pg_log_info (char*) ; 
 int /*<<< orphan*/  run_simple_command (char*) ; 
 char* run_simple_query (char*) ; 
 scalar_t__ showprogress ; 
 scalar_t__ strcmp (char*,char*) ; 

void
libpqConnect(const char *connstr)
{
	char	   *str;
	PGresult   *res;

	conn = PQconnectdb(connstr);
	if (PQstatus(conn) == CONNECTION_BAD)
		pg_fatal("could not connect to server: %s",
				 PQerrorMessage(conn));

	if (showprogress)
		pg_log_info("connected to server");

	/* disable all types of timeouts */
	run_simple_command("SET statement_timeout = 0");
	run_simple_command("SET lock_timeout = 0");
	run_simple_command("SET idle_in_transaction_session_timeout = 0");

	res = PQexec(conn, ALWAYS_SECURE_SEARCH_PATH_SQL);
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
		pg_fatal("could not clear search_path: %s",
				 PQresultErrorMessage(res));
	PQclear(res);

	/*
	 * Check that the server is not in hot standby mode. There is no
	 * fundamental reason that couldn't be made to work, but it doesn't
	 * currently because we use a temporary table. Better to check for it
	 * explicitly than error out, for a better error message.
	 */
	str = run_simple_query("SELECT pg_is_in_recovery()");
	if (strcmp(str, "f") != 0)
		pg_fatal("source server must not be in recovery mode");
	pg_free(str);

	/*
	 * Also check that full_page_writes is enabled.  We can get torn pages if
	 * a page is modified while we read it with pg_read_binary_file(), and we
	 * rely on full page images to fix them.
	 */
	str = run_simple_query("SHOW full_page_writes");
	if (strcmp(str, "on") != 0)
		pg_fatal("full_page_writes must be enabled in the source server");
	pg_free(str);

	/*
	 * Although we don't do any "real" updates, we do work with a temporary
	 * table. We don't care about synchronous commit for that. It doesn't
	 * otherwise matter much, but if the server is using synchronous
	 * replication, and replication isn't working for some reason, we don't
	 * want to get stuck, waiting for it to start working again.
	 */
	run_simple_command("SET synchronous_commit = off");
}