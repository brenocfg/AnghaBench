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
struct TYPE_5__ {int /*<<< orphan*/  in_txn; } ;
typedef  TYPE_1__ pdo_dbh_t ;

/* Variables and functions */
 int pdo_pgsql_transaction_cmd (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  pgsql_handle_in_transaction (TYPE_1__*) ; 

__attribute__((used)) static int pgsql_handle_commit(pdo_dbh_t *dbh)
{
	int ret = pdo_pgsql_transaction_cmd("COMMIT", dbh);

	/* When deferred constraints are used the commit could
	   fail, and a ROLLBACK implicitly ran. See bug #67462 */
	if (!ret) {
		dbh->in_txn = pgsql_handle_in_transaction(dbh);
	}

	return ret;
}