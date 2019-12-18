#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* lobjfuncs; int /*<<< orphan*/  errorMessage; } ;
struct TYPE_9__ {int /*<<< orphan*/  integer; } ;
struct TYPE_11__ {int isint; int len; TYPE_1__ u; } ;
struct TYPE_10__ {scalar_t__ fn_lo_create; } ;
typedef  TYPE_3__ PQArgBlock ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_4__ PGconn ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQfn (TYPE_4__*,scalar_t__,int*,int*,int,TYPE_3__*,int) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 scalar_t__ lo_initialize (TYPE_4__*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

Oid
lo_create(PGconn *conn, Oid lobjId)
{
	PQArgBlock	argv[1];
	PGresult   *res;
	int			retval;
	int			result_len;

	if (conn == NULL || conn->lobjfuncs == NULL)
	{
		if (lo_initialize(conn) < 0)
			return InvalidOid;
	}

	/* Must check this on-the-fly because it's not there pre-8.1 */
	if (conn->lobjfuncs->fn_lo_create == 0)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("cannot determine OID of function lo_create\n"));
		return InvalidOid;
	}

	argv[0].isint = 1;
	argv[0].len = 4;
	argv[0].u.integer = lobjId;
	res = PQfn(conn, conn->lobjfuncs->fn_lo_create,
			   &retval, &result_len, 1, argv, 1);
	if (PQresultStatus(res) == PGRES_COMMAND_OK)
	{
		PQclear(res);
		return (Oid) retval;
	}
	else
	{
		PQclear(res);
		return InvalidOid;
	}
}