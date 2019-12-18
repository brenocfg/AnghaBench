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
struct statement {int /*<<< orphan*/ * results; int /*<<< orphan*/  compat; TYPE_1__* connection; int /*<<< orphan*/  lineno; } ;
struct TYPE_2__ {int /*<<< orphan*/  connection; int /*<<< orphan*/  autocommit; } ;

/* Variables and functions */
 scalar_t__ PQTRANS_IDLE ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ PQtransactionStatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecpg_check_PQresult (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecpg_free_params (struct statement*,int) ; 

bool
ecpg_autostart_transaction(struct statement *stmt)
{
	if (PQtransactionStatus(stmt->connection->connection) == PQTRANS_IDLE && !stmt->connection->autocommit)
	{
		stmt->results = PQexec(stmt->connection->connection, "begin transaction");
		if (!ecpg_check_PQresult(stmt->results, stmt->lineno, stmt->connection->connection, stmt->compat))
		{
			ecpg_free_params(stmt, false);
			return false;
		}
		PQclear(stmt->results);
		stmt->results = NULL;
	}
	return true;
}