#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sqlerrmc; int /*<<< orphan*/  sqlerrml; } ;
struct sqlca_t {TYPE_1__ sqlerrm; int /*<<< orphan*/  sqlcode; int /*<<< orphan*/  sqlstate; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 scalar_t__ CONNECTION_BAD ; 
 int /*<<< orphan*/  ECPG_DUPLICATE_KEY ; 
 int /*<<< orphan*/  ECPG_INFORMIX_DUPLICATE_KEY ; 
 int /*<<< orphan*/  ECPG_INFORMIX_SUBSELECT_NOT_ONE ; 
 int /*<<< orphan*/  ECPG_PGSQL ; 
 char* ECPG_SQLSTATE_ECPG_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ECPG_SUBSELECT_NOT_ONE ; 
 int /*<<< orphan*/  ECPGfree_auto_mem () ; 
 struct sqlca_t* ECPGget_sqlca () ; 
 scalar_t__ INFORMIX_MODE (int) ; 
 int /*<<< orphan*/  PG_DIAG_MESSAGE_PRIMARY ; 
 int /*<<< orphan*/  PG_DIAG_SQLSTATE ; 
 char* PQerrorMessage (int /*<<< orphan*/ *) ; 
 char* PQresultErrorField (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ *) ; 
 char* ecpg_gettext (char*) ; 
 int /*<<< orphan*/  ecpg_log (char*,...) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

void
ecpg_raise_backend(int line, PGresult *result, PGconn *conn, int compat)
{
	struct sqlca_t *sqlca = ECPGget_sqlca();
	char	   *sqlstate;
	char	   *message;

	if (sqlca == NULL)
	{
		ecpg_log("out of memory");
		ECPGfree_auto_mem();
		return;
	}

	if (result)
	{
		sqlstate = PQresultErrorField(result, PG_DIAG_SQLSTATE);
		if (sqlstate == NULL)
			sqlstate = ECPG_SQLSTATE_ECPG_INTERNAL_ERROR;
		message = PQresultErrorField(result, PG_DIAG_MESSAGE_PRIMARY);
	}
	else
	{
		sqlstate = ECPG_SQLSTATE_ECPG_INTERNAL_ERROR;
		message = PQerrorMessage(conn);
	}

	if (strcmp(sqlstate, ECPG_SQLSTATE_ECPG_INTERNAL_ERROR) == 0)
	{
		/*
		 * we might get here if the connection breaks down, so let's check for
		 * this instead of giving just the generic internal error
		 */
		if (PQstatus(conn) == CONNECTION_BAD)
		{
			sqlstate = "57P02";
			message = ecpg_gettext("the connection to the server was lost");
		}
	}

	/* copy error message */
	snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc), "%s on line %d", message, line);
	sqlca->sqlerrm.sqlerrml = strlen(sqlca->sqlerrm.sqlerrmc);

	/* copy SQLSTATE */
	strncpy(sqlca->sqlstate, sqlstate, sizeof(sqlca->sqlstate));

	/* assign SQLCODE for backward compatibility */
	if (strncmp(sqlca->sqlstate, "23505", sizeof(sqlca->sqlstate)) == 0)
		sqlca->sqlcode = INFORMIX_MODE(compat) ? ECPG_INFORMIX_DUPLICATE_KEY : ECPG_DUPLICATE_KEY;
	else if (strncmp(sqlca->sqlstate, "21000", sizeof(sqlca->sqlstate)) == 0)
		sqlca->sqlcode = INFORMIX_MODE(compat) ? ECPG_INFORMIX_SUBSELECT_NOT_ONE : ECPG_SUBSELECT_NOT_ONE;
	else
		sqlca->sqlcode = ECPG_PGSQL;

	/* %.*s is safe here as long as sqlstate is all-ASCII */
	ecpg_log("raising sqlstate %.*s (sqlcode %ld): %s\n",
			 (int) sizeof(sqlca->sqlstate), sqlca->sqlstate, sqlca->sqlcode, sqlca->sqlerrm.sqlerrmc);

	/* free all memory we have allocated for the user */
	ECPGfree_auto_mem();
}