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
typedef  enum trivalue { ____Placeholder_trivalue } trivalue ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/ * connectDatabase (char const*,char const*,char const*,char const*,int,char const*,int,int,int) ; 

PGconn *
connectMaintenanceDatabase(const char *maintenance_db,
						   const char *pghost, const char *pgport,
						   const char *pguser, enum trivalue prompt_password,
						   const char *progname, bool echo)
{
	PGconn	   *conn;

	/* If a maintenance database name was specified, just connect to it. */
	if (maintenance_db)
		return connectDatabase(maintenance_db, pghost, pgport, pguser,
							   prompt_password, progname, echo, false, false);

	/* Otherwise, try postgres first and then template1. */
	conn = connectDatabase("postgres", pghost, pgport, pguser, prompt_password,
						   progname, echo, true, false);
	if (!conn)
		conn = connectDatabase("template1", pghost, pgport, pguser,
							   prompt_password, progname, echo, false, false);

	return conn;
}