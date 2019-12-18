#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  errorMessage; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int PQsendQueryGuts (TYPE_1__*,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *,char const* const*,int const*,int const*,int) ; 
 int /*<<< orphan*/  PQsendQueryStart (TYPE_1__*) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
PQsendQueryPrepared(PGconn *conn,
					const char *stmtName,
					int nParams,
					const char *const *paramValues,
					const int *paramLengths,
					const int *paramFormats,
					int resultFormat)
{
	if (!PQsendQueryStart(conn))
		return 0;

	/* check the arguments */
	if (!stmtName)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("statement name is a null pointer\n"));
		return 0;
	}
	if (nParams < 0 || nParams > 65535)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("number of parameters must be between 0 and 65535\n"));
		return 0;
	}

	return PQsendQueryGuts(conn,
						   NULL,	/* no command to parse */
						   stmtName,
						   nParams,
						   NULL,	/* no param types */
						   paramValues,
						   paramLengths,
						   paramFormats,
						   resultFormat);
}