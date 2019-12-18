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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int PQsendQueryGuts (TYPE_1__*,char const*,char*,int,int /*<<< orphan*/  const*,char const* const*,int const*,int const*,int) ; 
 int /*<<< orphan*/  PQsendQueryStart (TYPE_1__*) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
PQsendQueryParams(PGconn *conn,
				  const char *command,
				  int nParams,
				  const Oid *paramTypes,
				  const char *const *paramValues,
				  const int *paramLengths,
				  const int *paramFormats,
				  int resultFormat)
{
	if (!PQsendQueryStart(conn))
		return 0;

	/* check the arguments */
	if (!command)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("command string is a null pointer\n"));
		return 0;
	}
	if (nParams < 0 || nParams > 65535)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("number of parameters must be between 0 and 65535\n"));
		return 0;
	}

	return PQsendQueryGuts(conn,
						   command,
						   "",	/* use unnamed statement */
						   nParams,
						   paramTypes,
						   paramValues,
						   paramLengths,
						   paramFormats,
						   resultFormat);
}