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
struct connection {char* name; scalar_t__ connection; int /*<<< orphan*/  autocommit; } ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  ECPG_COMPAT_PGSQL ; 
 scalar_t__ PQTRANS_IDLE ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (scalar_t__,char const*) ; 
 scalar_t__ PQtransactionStatus (scalar_t__) ; 
 int /*<<< orphan*/  ecpg_check_PQresult (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 
 struct connection* ecpg_get_connection (char const*) ; 
 int /*<<< orphan*/  ecpg_init (struct connection*,char const*,int) ; 
 int /*<<< orphan*/  ecpg_log (char*,int,char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

bool
ECPGtrans(int lineno, const char *connection_name, const char *transaction)
{
	PGresult   *res;
	struct connection *con = ecpg_get_connection(connection_name);

	if (!ecpg_init(con, connection_name, lineno))
		return false;

	ecpg_log("ECPGtrans on line %d: action \"%s\"; connection \"%s\"\n", lineno, transaction, con ? con->name : "null");

	/* if we have no connection we just simulate the command */
	if (con && con->connection)
	{
		/*
		 * If we got a transaction command but have no open transaction, we
		 * have to start one, unless we are in autocommit, where the
		 * developers have to take care themselves. However, if the command is
		 * a begin statement, we just execute it once. And if the command is
		 * commit or rollback prepared, we don't execute it.
		 */
		if (PQtransactionStatus(con->connection) == PQTRANS_IDLE &&
			!con->autocommit &&
			strncmp(transaction, "begin", 5) != 0 &&
			strncmp(transaction, "start", 5) != 0 &&
			strncmp(transaction, "commit prepared", 15) != 0 &&
			strncmp(transaction, "rollback prepared", 17) != 0)
		{
			res = PQexec(con->connection, "begin transaction");
			if (!ecpg_check_PQresult(res, lineno, con->connection, ECPG_COMPAT_PGSQL))
				return false;
			PQclear(res);
		}

		res = PQexec(con->connection, transaction);
		if (!ecpg_check_PQresult(res, lineno, con->connection, ECPG_COMPAT_PGSQL))
			return false;
		PQclear(res);
	}

	return true;
}