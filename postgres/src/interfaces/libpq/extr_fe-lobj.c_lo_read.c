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
struct TYPE_9__ {int integer; } ;
struct TYPE_11__ {int isint; int len; TYPE_1__ u; } ;
struct TYPE_10__ {int /*<<< orphan*/  fn_lo_read; } ;
typedef  TYPE_3__ PQArgBlock ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_4__ PGconn ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQfn (TYPE_4__*,int /*<<< orphan*/ ,void*,int*,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 scalar_t__ lo_initialize (TYPE_4__*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
lo_read(PGconn *conn, int fd, char *buf, size_t len)
{
	PQArgBlock	argv[2];
	PGresult   *res;
	int			result_len;

	if (conn == NULL || conn->lobjfuncs == NULL)
	{
		if (lo_initialize(conn) < 0)
			return -1;
	}

	/*
	 * Long ago, somebody thought it'd be a good idea to declare this function
	 * as taking size_t ... but the underlying backend function only accepts a
	 * signed int32 length.  So throw error if the given value overflows
	 * int32.
	 */
	if (len > (size_t) INT_MAX)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("argument of lo_read exceeds integer range\n"));
		return -1;
	}

	argv[0].isint = 1;
	argv[0].len = 4;
	argv[0].u.integer = fd;

	argv[1].isint = 1;
	argv[1].len = 4;
	argv[1].u.integer = (int) len;

	res = PQfn(conn, conn->lobjfuncs->fn_lo_read,
			   (void *) buf, &result_len, 0, argv, 2);
	if (PQresultStatus(res) == PGRES_COMMAND_OK)
	{
		PQclear(res);
		return result_len;
	}
	else
	{
		PQclear(res);
		return -1;
	}
}