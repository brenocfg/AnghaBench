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
struct TYPE_2__ {int /*<<< orphan*/  db; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int PGTransactionStatusType ;

/* Variables and functions */
#define  PQTRANS_IDLE 130 
#define  PQTRANS_INERROR 129 
#define  PQTRANS_INTRANS 128 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQtransactionStatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PSQLexec (char*) ; 
 int /*<<< orphan*/  pg_log_error (char*,char const*) ; 
 TYPE_1__ pset ; 

__attribute__((used)) static bool
start_lo_xact(const char *operation, bool *own_transaction)
{
	PGTransactionStatusType tstatus;
	PGresult   *res;

	*own_transaction = false;

	if (!pset.db)
	{
		pg_log_error("%s: not connected to a database", operation);
		return false;
	}

	tstatus = PQtransactionStatus(pset.db);

	switch (tstatus)
	{
		case PQTRANS_IDLE:
			/* need to start our own xact */
			if (!(res = PSQLexec("BEGIN")))
				return false;
			PQclear(res);
			*own_transaction = true;
			break;
		case PQTRANS_INTRANS:
			/* use the existing xact */
			break;
		case PQTRANS_INERROR:
			pg_log_error("%s: current transaction is aborted", operation);
			return false;
		default:
			pg_log_error("%s: unknown transaction status", operation);
			return false;
	}

	return true;
}