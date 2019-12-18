#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  streamConn; } ;
typedef  TYPE_1__ WalReceiverConn ;
struct TYPE_8__ {int /*<<< orphan*/  err; void* status; } ;
typedef  TYPE_2__ WalRcvExecResult ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidOid ; 
 scalar_t__ MyDatabaseId ; 
#define  PGRES_BAD_RESPONSE 137 
#define  PGRES_COMMAND_OK 136 
#define  PGRES_COPY_BOTH 135 
#define  PGRES_COPY_IN 134 
#define  PGRES_COPY_OUT 133 
#define  PGRES_EMPTY_QUERY 132 
#define  PGRES_FATAL_ERROR 131 
#define  PGRES_NONFATAL_ERROR 130 
#define  PGRES_SINGLE_TUPLE 129 
#define  PGRES_TUPLES_OK 128 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ ) ; 
 int PQresultStatus (int /*<<< orphan*/ *) ; 
 void* WALRCV_ERROR ; 
 void* WALRCV_OK_COMMAND ; 
 void* WALRCV_OK_COPY_BOTH ; 
 void* WALRCV_OK_COPY_IN ; 
 void* WALRCV_OK_COPY_OUT ; 
 void* WALRCV_OK_TUPLES ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/ * libpqrcv_PQexec (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  libpqrcv_processTuples (int /*<<< orphan*/ *,TYPE_2__*,int const,int /*<<< orphan*/  const*) ; 
 TYPE_2__* palloc0 (int) ; 
 int /*<<< orphan*/  pchomp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static WalRcvExecResult *
libpqrcv_exec(WalReceiverConn *conn, const char *query,
			  const int nRetTypes, const Oid *retTypes)
{
	PGresult   *pgres = NULL;
	WalRcvExecResult *walres = palloc0(sizeof(WalRcvExecResult));

	if (MyDatabaseId == InvalidOid)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("the query interface requires a database connection")));

	pgres = libpqrcv_PQexec(conn->streamConn, query);

	switch (PQresultStatus(pgres))
	{
		case PGRES_SINGLE_TUPLE:
		case PGRES_TUPLES_OK:
			walres->status = WALRCV_OK_TUPLES;
			libpqrcv_processTuples(pgres, walres, nRetTypes, retTypes);
			break;

		case PGRES_COPY_IN:
			walres->status = WALRCV_OK_COPY_IN;
			break;

		case PGRES_COPY_OUT:
			walres->status = WALRCV_OK_COPY_OUT;
			break;

		case PGRES_COPY_BOTH:
			walres->status = WALRCV_OK_COPY_BOTH;
			break;

		case PGRES_COMMAND_OK:
			walres->status = WALRCV_OK_COMMAND;
			break;

			/* Empty query is considered error. */
		case PGRES_EMPTY_QUERY:
			walres->status = WALRCV_ERROR;
			walres->err = _("empty query");
			break;

		case PGRES_NONFATAL_ERROR:
		case PGRES_FATAL_ERROR:
		case PGRES_BAD_RESPONSE:
			walres->status = WALRCV_ERROR;
			walres->err = pchomp(PQerrorMessage(conn->streamConn));
			break;
	}

	PQclear(pgres);

	return walres;
}