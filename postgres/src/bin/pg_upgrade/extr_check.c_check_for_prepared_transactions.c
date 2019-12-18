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
typedef  int /*<<< orphan*/  ClusterInfo ;

/* Variables and functions */
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 scalar_t__ PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_ok () ; 
 int /*<<< orphan*/ * connectToServer (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * executeQueryOrDie (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  old_cluster ; 
 int /*<<< orphan*/  pg_fatal (char*) ; 
 int /*<<< orphan*/  prep_status (char*) ; 

__attribute__((used)) static void
check_for_prepared_transactions(ClusterInfo *cluster)
{
	PGresult   *res;
	PGconn	   *conn = connectToServer(cluster, "template1");

	prep_status("Checking for prepared transactions");

	res = executeQueryOrDie(conn,
							"SELECT * "
							"FROM pg_catalog.pg_prepared_xacts");

	if (PQntuples(res) != 0)
	{
		if (cluster == &old_cluster)
			pg_fatal("The source cluster contains prepared transactions\n");
		else
			pg_fatal("The target cluster contains prepared transactions\n");
	}

	PQclear(res);

	PQfinish(conn);

	check_ok();
}