#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  query ;
struct TYPE_5__ {int /*<<< orphan*/  major_version; } ;
struct TYPE_4__ {int num_old_tablespaces; char** old_tablespaces; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int GET_MAJOR_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_FATAL ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int QUERY_ALLOC ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * connectToServer (TYPE_2__*,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * executeQueryOrDie (int /*<<< orphan*/ *,char*,char*) ; 
 TYPE_2__ old_cluster ; 
 TYPE_1__ os_info ; 
 scalar_t__ pg_malloc (int) ; 
 char* pg_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_status (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static void
get_tablespace_paths(void)
{
	PGconn	   *conn = connectToServer(&old_cluster, "template1");
	PGresult   *res;
	int			tblnum;
	int			i_spclocation;
	char		query[QUERY_ALLOC];

	snprintf(query, sizeof(query),
			 "SELECT	%s "
			 "FROM	pg_catalog.pg_tablespace "
			 "WHERE	spcname != 'pg_default' AND "
			 "		spcname != 'pg_global'",
	/* 9.2 removed the spclocation column */
			 (GET_MAJOR_VERSION(old_cluster.major_version) <= 901) ?
			 "spclocation" : "pg_catalog.pg_tablespace_location(oid) AS spclocation");

	res = executeQueryOrDie(conn, "%s", query);

	if ((os_info.num_old_tablespaces = PQntuples(res)) != 0)
		os_info.old_tablespaces = (char **) pg_malloc(
													  os_info.num_old_tablespaces * sizeof(char *));
	else
		os_info.old_tablespaces = NULL;

	i_spclocation = PQfnumber(res, "spclocation");

	for (tblnum = 0; tblnum < os_info.num_old_tablespaces; tblnum++)
	{
		struct stat statBuf;

		os_info.old_tablespaces[tblnum] = pg_strdup(
													PQgetvalue(res, tblnum, i_spclocation));

		/*
		 * Check that the tablespace path exists and is a directory.
		 * Effectively, this is checking only for tables/indexes in
		 * non-existent tablespace directories.  Databases located in
		 * non-existent tablespaces already throw a backend error.
		 * Non-existent tablespace directories can occur when a data directory
		 * that contains user tablespaces is moved as part of pg_upgrade
		 * preparation and the symbolic links are not updated.
		 */
		if (stat(os_info.old_tablespaces[tblnum], &statBuf) != 0)
		{
			if (errno == ENOENT)
				report_status(PG_FATAL,
							  "tablespace directory \"%s\" does not exist\n",
							  os_info.old_tablespaces[tblnum]);
			else
				report_status(PG_FATAL,
							  "could not stat tablespace directory \"%s\": %s\n",
							  os_info.old_tablespaces[tblnum], strerror(errno));
		}
		if (!S_ISDIR(statBuf.st_mode))
			report_status(PG_FATAL,
						  "tablespace path \"%s\" is not a directory\n",
						  os_info.old_tablespaces[tblnum]);
	}

	PQclear(res);

	PQfinish(conn);

	return;
}