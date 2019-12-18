#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* val; int /*<<< orphan*/ * keyword; } ;
typedef  TYPE_1__ PQconninfoOption ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_S_R_E_PROHIBITED_SQL_STATEMENT_ATTEMPTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PQconninfoFree (TYPE_1__*) ; 
 TYPE_1__* PQconninfoParse (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  superuser () ; 

__attribute__((used)) static void
dblink_connstr_check(const char *connstr)
{
	if (!superuser())
	{
		PQconninfoOption *options;
		PQconninfoOption *option;
		bool		connstr_gives_password = false;

		options = PQconninfoParse(connstr, NULL);
		if (options)
		{
			for (option = options; option->keyword != NULL; option++)
			{
				if (strcmp(option->keyword, "password") == 0)
				{
					if (option->val != NULL && option->val[0] != '\0')
					{
						connstr_gives_password = true;
						break;
					}
				}
			}
			PQconninfoFree(options);
		}

		if (!connstr_gives_password)
			ereport(ERROR,
					(errcode(ERRCODE_S_R_E_PROHIBITED_SQL_STATEMENT_ATTEMPTED),
					 errmsg("password is required"),
					 errdetail("Non-superusers must provide a password in the connection string.")));
	}
}