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
typedef  enum COMPAT_MODE { ____Placeholder_COMPAT_MODE } COMPAT_MODE ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  ECPG_EMPTY ; 
 int /*<<< orphan*/  ECPG_SQLSTATE_ECPG_INTERNAL_ERROR ; 
#define  PGRES_BAD_RESPONSE 135 
#define  PGRES_COMMAND_OK 134 
#define  PGRES_COPY_IN 133 
#define  PGRES_COPY_OUT 132 
#define  PGRES_EMPTY_QUERY 131 
#define  PGRES_FATAL_ERROR 130 
#define  PGRES_NONFATAL_ERROR 129 
#define  PGRES_TUPLES_OK 128 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQendcopy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQresultErrorMessage (int /*<<< orphan*/ *) ; 
 int PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecpg_log (char*,int,...) ; 
 int /*<<< orphan*/  ecpg_raise (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecpg_raise_backend (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

bool
ecpg_check_PQresult(PGresult *results, int lineno, PGconn *connection, enum COMPAT_MODE compat)
{
	if (results == NULL)
	{
		ecpg_log("ecpg_check_PQresult on line %d: no result - %s", lineno, PQerrorMessage(connection));
		ecpg_raise_backend(lineno, NULL, connection, compat);
		return false;
	}

	switch (PQresultStatus(results))
	{

		case PGRES_TUPLES_OK:
			return true;
			break;
		case PGRES_EMPTY_QUERY:
			/* do nothing */
			ecpg_raise(lineno, ECPG_EMPTY, ECPG_SQLSTATE_ECPG_INTERNAL_ERROR, NULL);
			PQclear(results);
			return false;
			break;
		case PGRES_COMMAND_OK:
			return true;
			break;
		case PGRES_NONFATAL_ERROR:
		case PGRES_FATAL_ERROR:
		case PGRES_BAD_RESPONSE:
			ecpg_log("ecpg_check_PQresult on line %d: bad response - %s", lineno, PQresultErrorMessage(results));
			ecpg_raise_backend(lineno, results, connection, compat);
			PQclear(results);
			return false;
			break;
		case PGRES_COPY_OUT:
			return true;
			break;
		case PGRES_COPY_IN:
			ecpg_log("ecpg_check_PQresult on line %d: COPY IN data transfer in progress\n", lineno);
			PQendcopy(connection);
			PQclear(results);
			return false;
			break;
		default:
			ecpg_log("ecpg_check_PQresult on line %d: unknown execution status type\n",
					 lineno);
			ecpg_raise_backend(lineno, results, connection, compat);
			PQclear(results);
			return false;
			break;
	}
}