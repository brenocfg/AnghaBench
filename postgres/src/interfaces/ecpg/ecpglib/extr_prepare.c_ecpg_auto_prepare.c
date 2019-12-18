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
struct prepared_statement {int dummy; } ;
struct connection {int dummy; } ;
struct TYPE_2__ {char* stmtID; int /*<<< orphan*/  execs; } ;

/* Variables and functions */
 int AddStmtToCache (int,char*,char const*,int const,char const*) ; 
 int /*<<< orphan*/  ECPGprepare (int,char const*,int /*<<< orphan*/ ,char*,char const*) ; 
 int STMTID_SIZE ; 
 int SearchStmtCache (char const*) ; 
 struct prepared_statement* ecpg_find_prepared_statement (char*,struct connection*,int /*<<< orphan*/ *) ; 
 struct connection* ecpg_get_connection (char const*) ; 
 int /*<<< orphan*/  ecpg_log (char*,int,...) ; 
 char* ecpg_strdup (char*,int) ; 
 int /*<<< orphan*/  nextStmtID ; 
 int /*<<< orphan*/  prepare_common (int,struct connection*,char*,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* stmtCacheEntries ; 

bool
ecpg_auto_prepare(int lineno, const char *connection_name, const int compat, char **name, const char *query)
{
	int			entNo;

	/* search the statement cache for this statement */
	entNo = SearchStmtCache(query);

	/* if not found - add the statement to the cache */
	if (entNo)
	{
		char	   *stmtID;
		struct connection *con;
		struct prepared_statement *prep;

		ecpg_log("ecpg_auto_prepare on line %d: statement found in cache; entry %d\n", lineno, entNo);

		stmtID = stmtCacheEntries[entNo].stmtID;

		con = ecpg_get_connection(connection_name);
		prep = ecpg_find_prepared_statement(stmtID, con, NULL);
		/* This prepared name doesn't exist on this connection. */
		if (!prep && !prepare_common(lineno, con, stmtID, query))
			return false;

		*name = ecpg_strdup(stmtID, lineno);
	}
	else
	{
		char		stmtID[STMTID_SIZE];

		ecpg_log("ecpg_auto_prepare on line %d: statement not in cache; inserting\n", lineno);

		/* generate a statement ID */
		sprintf(stmtID, "ecpg%d", nextStmtID++);

		if (!ECPGprepare(lineno, connection_name, 0, stmtID, query))
			return false;

		entNo = AddStmtToCache(lineno, stmtID, connection_name, compat, query);
		if (entNo < 0)
			return false;

		*name = ecpg_strdup(stmtID, lineno);
	}

	/* increase usage counter */
	stmtCacheEntries[entNo].execs++;

	return true;
}