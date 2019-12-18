#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ resultStatus; } ;
struct TYPE_9__ {char* data; } ;
typedef  TYPE_1__ PQExpBufferData ;
typedef  TYPE_2__ PGresult ;
typedef  int /*<<< orphan*/  PGVerbosity ;
typedef  int /*<<< orphan*/  PGContextVisibility ;

/* Variables and functions */
 scalar_t__ PGRES_FATAL_ERROR ; 
 scalar_t__ PGRES_NONFATAL_ERROR ; 
 scalar_t__ PQExpBufferDataBroken (TYPE_1__) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  pqBuildErrorMessage3 (TYPE_1__*,TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_1__*) ; 

char *
PQresultVerboseErrorMessage(const PGresult *res,
							PGVerbosity verbosity,
							PGContextVisibility show_context)
{
	PQExpBufferData workBuf;

	/*
	 * Because the caller is expected to free the result string, we must
	 * strdup any constant result.  We use plain strdup and document that
	 * callers should expect NULL if out-of-memory.
	 */
	if (!res ||
		(res->resultStatus != PGRES_FATAL_ERROR &&
		 res->resultStatus != PGRES_NONFATAL_ERROR))
		return strdup(libpq_gettext("PGresult is not an error result\n"));

	initPQExpBuffer(&workBuf);

	/*
	 * Currently, we pass this off to fe-protocol3.c in all cases; it will
	 * behave reasonably sanely with an error reported by fe-protocol2.c as
	 * well.  If necessary, we could record the protocol version in PGresults
	 * so as to be able to invoke a version-specific message formatter, but
	 * for now there's no need.
	 */
	pqBuildErrorMessage3(&workBuf, res, verbosity, show_context);

	/* If insufficient memory to format the message, fail cleanly */
	if (PQExpBufferDataBroken(workBuf))
	{
		termPQExpBuffer(&workBuf);
		return strdup(libpq_gettext("out of memory\n"));
	}

	return workBuf.data;
}