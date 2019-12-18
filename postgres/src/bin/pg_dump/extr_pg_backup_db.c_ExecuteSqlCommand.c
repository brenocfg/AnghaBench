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
struct TYPE_4__ {int pgCopyIn; int /*<<< orphan*/ * connection; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  TYPE_1__ ArchiveHandle ;

/* Variables and functions */
#define  PGRES_COMMAND_OK 131 
#define  PGRES_COPY_IN 130 
#define  PGRES_EMPTY_QUERY 129 
#define  PGRES_TUPLES_OK 128 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ *,char const*) ; 
 int PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warn_or_exit_horribly (TYPE_1__*,char*,char const*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void
ExecuteSqlCommand(ArchiveHandle *AH, const char *qry, const char *desc)
{
	PGconn	   *conn = AH->connection;
	PGresult   *res;

#ifdef NOT_USED
	fprintf(stderr, "Executing: '%s'\n\n", qry);
#endif
	res = PQexec(conn, qry);

	switch (PQresultStatus(res))
	{
		case PGRES_COMMAND_OK:
		case PGRES_TUPLES_OK:
		case PGRES_EMPTY_QUERY:
			/* A-OK */
			break;
		case PGRES_COPY_IN:
			/* Assume this is an expected result */
			AH->pgCopyIn = true;
			break;
		default:
			/* trouble */
			warn_or_exit_horribly(AH, "%s: %sCommand was: %s",
								  desc, PQerrorMessage(conn), qry);
			break;
	}

	PQclear(res);
}