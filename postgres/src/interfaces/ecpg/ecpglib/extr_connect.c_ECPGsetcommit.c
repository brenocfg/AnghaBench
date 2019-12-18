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
struct connection {int autocommit; int /*<<< orphan*/  connection; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  ECPG_COMPAT_PGSQL ; 
 scalar_t__ PQTRANS_IDLE ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ PQtransactionStatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecpg_check_PQresult (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct connection* ecpg_get_connection (char const*) ; 
 int /*<<< orphan*/  ecpg_init (struct connection*,char const*,int) ; 
 int /*<<< orphan*/  ecpg_log (char*,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int /*<<< orphan*/ ) ; 

bool
ECPGsetcommit(int lineno, const char *mode, const char *connection_name)
{
	struct connection *con = ecpg_get_connection(connection_name);
	PGresult   *results;

	if (!ecpg_init(con, connection_name, lineno))
		return false;

	ecpg_log("ECPGsetcommit on line %d: action \"%s\"; connection \"%s\"\n", lineno, mode, con->name);

	if (con->autocommit && strncmp(mode, "off", strlen("off")) == 0)
	{
		if (PQtransactionStatus(con->connection) == PQTRANS_IDLE)
		{
			results = PQexec(con->connection, "begin transaction");
			if (!ecpg_check_PQresult(results, lineno, con->connection, ECPG_COMPAT_PGSQL))
				return false;
			PQclear(results);
		}
		con->autocommit = false;
	}
	else if (!con->autocommit && strncmp(mode, "on", strlen("on")) == 0)
	{
		if (PQtransactionStatus(con->connection) != PQTRANS_IDLE)
		{
			results = PQexec(con->connection, "commit");
			if (!ecpg_check_PQresult(results, lineno, con->connection, ECPG_COMPAT_PGSQL))
				return false;
			PQclear(results);
		}
		con->autocommit = true;
	}

	return true;
}