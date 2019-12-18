#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  socket_string ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_10__ {TYPE_2__* running_cluster; } ;
struct TYPE_8__ {scalar_t__ cat_ver; } ;
struct TYPE_9__ {char* sockdir; char* bindir; char* pgconfig; int port; char* pgopts; TYPE_1__ controldata; int /*<<< orphan*/  major_version; } ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  TYPE_2__ ClusterInfo ;

/* Variables and functions */
 scalar_t__ BINARY_UPGRADE_SERVER_FLAG_CAT_VER ; 
 scalar_t__ CONNECTION_OK ; 
 int GET_MAJOR_VERSION (int /*<<< orphan*/ ) ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  PG_REPORT ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ *) ; 
 char* SERVER_LOG_FILE ; 
 int /*<<< orphan*/  SERVER_START_LOG_FILE ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int exec_prog (int /*<<< orphan*/ ,char*,int,int,char*,char*) ; 
 int /*<<< orphan*/ * get_db_conn (TYPE_2__*,char*) ; 
 TYPE_2__ new_cluster ; 
 TYPE_2__ old_cluster ; 
 TYPE_4__ os_info ; 
 int /*<<< orphan*/  pg_fatal (char*,...) ; 
 int /*<<< orphan*/  pg_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,...) ; 
 int /*<<< orphan*/  stop_postmaster_atexit ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

bool
start_postmaster(ClusterInfo *cluster, bool report_and_exit_on_error)
{
	char		cmd[MAXPGPATH * 4 + 1000];
	PGconn	   *conn;
	bool		pg_ctl_return = false;
	char		socket_string[MAXPGPATH + 200];

	static bool exit_hook_registered = false;

	if (!exit_hook_registered)
	{
		atexit(stop_postmaster_atexit);
		exit_hook_registered = true;
	}

	socket_string[0] = '\0';

#ifdef HAVE_UNIX_SOCKETS
	/* prevent TCP/IP connections, restrict socket access */
	strcat(socket_string,
		   " -c listen_addresses='' -c unix_socket_permissions=0700");

	/* Have a sockdir?	Tell the postmaster. */
	if (cluster->sockdir)
		snprintf(socket_string + strlen(socket_string),
				 sizeof(socket_string) - strlen(socket_string),
				 " -c %s='%s'",
				 (GET_MAJOR_VERSION(cluster->major_version) < 903) ?
				 "unix_socket_directory" : "unix_socket_directories",
				 cluster->sockdir);
#endif

	/*
	 * Since PG 9.1, we have used -b to disable autovacuum.  For earlier
	 * releases, setting autovacuum=off disables cleanup vacuum and analyze,
	 * but freeze vacuums can still happen, so we set
	 * autovacuum_freeze_max_age to its maximum.
	 * (autovacuum_multixact_freeze_max_age was introduced after 9.1, so there
	 * is no need to set that.)  We assume all datfrozenxid and relfrozenxid
	 * values are less than a gap of 2000000000 from the current xid counter,
	 * so autovacuum will not touch them.
	 *
	 * Turn off durability requirements to improve object creation speed, and
	 * we only modify the new cluster, so only use it there.  If there is a
	 * crash, the new cluster has to be recreated anyway.  fsync=off is a big
	 * win on ext4.
	 */
	snprintf(cmd, sizeof(cmd),
			 "\"%s/pg_ctl\" -w -l \"%s\" -D \"%s\" -o \"-p %d%s%s %s%s\" start",
			 cluster->bindir, SERVER_LOG_FILE, cluster->pgconfig, cluster->port,
			 (cluster->controldata.cat_ver >=
			  BINARY_UPGRADE_SERVER_FLAG_CAT_VER) ? " -b" :
			 " -c autovacuum=off -c autovacuum_freeze_max_age=2000000000",
			 (cluster == &new_cluster) ?
			 " -c synchronous_commit=off -c fsync=off -c full_page_writes=off" : "",
			 cluster->pgopts ? cluster->pgopts : "", socket_string);

	/*
	 * Don't throw an error right away, let connecting throw the error because
	 * it might supply a reason for the failure.
	 */
	pg_ctl_return = exec_prog(SERVER_START_LOG_FILE,
	/* pass both file names if they differ */
							  (strcmp(SERVER_LOG_FILE,
									  SERVER_START_LOG_FILE) != 0) ?
							  SERVER_LOG_FILE : NULL,
							  report_and_exit_on_error, false,
							  "%s", cmd);

	/* Did it fail and we are just testing if the server could be started? */
	if (!pg_ctl_return && !report_and_exit_on_error)
		return false;

	/*
	 * We set this here to make sure atexit() shuts down the server, but only
	 * if we started the server successfully.  We do it before checking for
	 * connectivity in case the server started but there is a connectivity
	 * failure.  If pg_ctl did not return success, we will exit below.
	 *
	 * Pre-9.1 servers do not have PQping(), so we could be leaving the server
	 * running if authentication was misconfigured, so someday we might went
	 * to be more aggressive about doing server shutdowns even if pg_ctl
	 * fails, but now (2013-08-14) it seems prudent to be cautious.  We don't
	 * want to shutdown a server that might have been accidentally started
	 * during the upgrade.
	 */
	if (pg_ctl_return)
		os_info.running_cluster = cluster;

	/*
	 * pg_ctl -w might have failed because the server couldn't be started, or
	 * there might have been a connection problem in _checking_ if the server
	 * has started.  Therefore, even if pg_ctl failed, we continue and test
	 * for connectivity in case we get a connection reason for the failure.
	 */
	if ((conn = get_db_conn(cluster, "template1")) == NULL ||
		PQstatus(conn) != CONNECTION_OK)
	{
		pg_log(PG_REPORT, "\nconnection to database failed: %s",
			   PQerrorMessage(conn));
		if (conn)
			PQfinish(conn);
		if (cluster == &old_cluster)
			pg_fatal("could not connect to source postmaster started with the command:\n"
					 "%s\n",
					 cmd);
		else
			pg_fatal("could not connect to target postmaster started with the command:\n"
					 "%s\n",
					 cmd);
	}
	PQfinish(conn);

	/*
	 * If pg_ctl failed, and the connection didn't fail, and
	 * report_and_exit_on_error is enabled, fail now.  This could happen if
	 * the server was already running.
	 */
	if (!pg_ctl_return)
	{
		if (cluster == &old_cluster)
			pg_fatal("pg_ctl failed to start the source server, or connection failed\n");
		else
			pg_fatal("pg_ctl failed to start the target server, or connection failed\n");
	}

	return true;
}