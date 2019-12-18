#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/ * PQgetResult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResetCancelConn () ; 
 int /*<<< orphan*/  SetCancelConn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  processQueryResult (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool
consumeQueryResult(PGconn *conn)
{
	bool		ok = true;
	PGresult   *result;

	SetCancelConn(conn);
	while ((result = PQgetResult(conn)) != NULL)
	{
		if (!processQueryResult(conn, result))
			ok = false;
	}
	ResetCancelConn();
	return ok;
}