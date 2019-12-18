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
struct TYPE_2__ {scalar_t__* sqlerrmc; int /*<<< orphan*/  sqlerrml; } ;
struct sqlca_t {int sqlcode; char* sqlwarn; TYPE_1__ sqlerrm; scalar_t__* sqlstate; } ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  ECPG_SQLSTATE_ACTIVE_SQL_TRANSACTION ; 
 int /*<<< orphan*/  ECPG_SQLSTATE_DUPLICATE_CURSOR ; 
 char* ECPG_SQLSTATE_ECPG_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ECPG_SQLSTATE_INVALID_CURSOR_NAME ; 
 int /*<<< orphan*/  ECPG_SQLSTATE_NO_ACTIVE_SQL_TRANSACTION ; 
 int ECPG_WARNING_IN_TRANSACTION ; 
 int ECPG_WARNING_NO_TRANSACTION ; 
 int ECPG_WARNING_PORTAL_EXISTS ; 
 int ECPG_WARNING_UNKNOWN_PORTAL ; 
 struct sqlca_t* ECPGget_sqlca () ; 
 int /*<<< orphan*/  PG_DIAG_MESSAGE_PRIMARY ; 
 int /*<<< orphan*/  PG_DIAG_SQLSTATE ; 
 char* PQresultErrorField (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 char* ecpg_gettext (char*) ; 
 int /*<<< orphan*/  ecpg_log (char*,...) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (scalar_t__*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,char*,int) ; 

__attribute__((used)) static void
ECPGnoticeReceiver(void *arg, const PGresult *result)
{
	char	   *sqlstate = PQresultErrorField(result, PG_DIAG_SQLSTATE);
	char	   *message = PQresultErrorField(result, PG_DIAG_MESSAGE_PRIMARY);
	struct sqlca_t *sqlca = ECPGget_sqlca();
	int			sqlcode;

	if (sqlca == NULL)
	{
		ecpg_log("out of memory");
		return;
	}

	(void) arg;					/* keep the compiler quiet */
	if (sqlstate == NULL)
		sqlstate = ECPG_SQLSTATE_ECPG_INTERNAL_ERROR;

	if (message == NULL)		/* Shouldn't happen, but need to be sure */
		message = ecpg_gettext("empty message text");

	/* these are not warnings */
	if (strncmp(sqlstate, "00", 2) == 0)
		return;

	ecpg_log("ECPGnoticeReceiver: %s\n", message);

	/* map to SQLCODE for backward compatibility */
	if (strcmp(sqlstate, ECPG_SQLSTATE_INVALID_CURSOR_NAME) == 0)
		sqlcode = ECPG_WARNING_UNKNOWN_PORTAL;
	else if (strcmp(sqlstate, ECPG_SQLSTATE_ACTIVE_SQL_TRANSACTION) == 0)
		sqlcode = ECPG_WARNING_IN_TRANSACTION;
	else if (strcmp(sqlstate, ECPG_SQLSTATE_NO_ACTIVE_SQL_TRANSACTION) == 0)
		sqlcode = ECPG_WARNING_NO_TRANSACTION;
	else if (strcmp(sqlstate, ECPG_SQLSTATE_DUPLICATE_CURSOR) == 0)
		sqlcode = ECPG_WARNING_PORTAL_EXISTS;
	else
		sqlcode = 0;

	strncpy(sqlca->sqlstate, sqlstate, sizeof(sqlca->sqlstate));
	sqlca->sqlcode = sqlcode;
	sqlca->sqlwarn[2] = 'W';
	sqlca->sqlwarn[0] = 'W';

	strncpy(sqlca->sqlerrm.sqlerrmc, message, sizeof(sqlca->sqlerrm.sqlerrmc));
	sqlca->sqlerrm.sqlerrmc[sizeof(sqlca->sqlerrm.sqlerrmc) - 1] = 0;
	sqlca->sqlerrm.sqlerrml = strlen(sqlca->sqlerrm.sqlerrmc);

	ecpg_log("raising sqlcode %d\n", sqlcode);
}