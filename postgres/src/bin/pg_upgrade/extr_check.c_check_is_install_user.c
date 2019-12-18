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
struct TYPE_2__ {int /*<<< orphan*/  user; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  int /*<<< orphan*/  ClusterInfo ;

/* Variables and functions */
 int BOOTSTRAP_SUPERUSERID ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int atooid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_ok () ; 
 int /*<<< orphan*/ * connectToServer (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * executeQueryOrDie (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  new_cluster ; 
 TYPE_1__ os_info ; 
 int /*<<< orphan*/  pg_fatal (char*,...) ; 
 int /*<<< orphan*/  prep_status (char*) ; 

__attribute__((used)) static void
check_is_install_user(ClusterInfo *cluster)
{
	PGresult   *res;
	PGconn	   *conn = connectToServer(cluster, "template1");

	prep_status("Checking database user is the install user");

	/* Can't use pg_authid because only superusers can view it. */
	res = executeQueryOrDie(conn,
							"SELECT rolsuper, oid "
							"FROM pg_catalog.pg_roles "
							"WHERE rolname = current_user "
							"AND rolname !~ '^pg_'");

	/*
	 * We only allow the install user in the new cluster (see comment below)
	 * and we preserve pg_authid.oid, so this must be the install user in the
	 * old cluster too.
	 */
	if (PQntuples(res) != 1 ||
		atooid(PQgetvalue(res, 0, 1)) != BOOTSTRAP_SUPERUSERID)
		pg_fatal("database user \"%s\" is not the install user\n",
				 os_info.user);

	PQclear(res);

	res = executeQueryOrDie(conn,
							"SELECT COUNT(*) "
							"FROM pg_catalog.pg_roles "
							"WHERE rolname !~ '^pg_'");

	if (PQntuples(res) != 1)
		pg_fatal("could not determine the number of users\n");

	/*
	 * We only allow the install user in the new cluster because other defined
	 * users might match users defined in the old cluster and generate an
	 * error during pg_dump restore.
	 */
	if (cluster == &new_cluster && atooid(PQgetvalue(res, 0, 0)) != 1)
		pg_fatal("Only the install user can be defined in the new cluster.\n");

	PQclear(res);

	PQfinish(conn);

	check_ok();
}