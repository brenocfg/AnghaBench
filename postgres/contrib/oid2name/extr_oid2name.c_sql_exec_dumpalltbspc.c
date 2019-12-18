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
typedef  int /*<<< orphan*/  todo ;
struct options {int /*<<< orphan*/  quiet; } ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 int /*<<< orphan*/  sql_exec (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void
sql_exec_dumpalltbspc(PGconn *conn, struct options *opts)
{
	char		todo[1024];

	snprintf(todo, sizeof(todo),
			 "SELECT oid AS \"Oid\", spcname as \"Tablespace Name\"\n"
			 "FROM pg_catalog.pg_tablespace");

	sql_exec(conn, todo, opts->quiet);
}