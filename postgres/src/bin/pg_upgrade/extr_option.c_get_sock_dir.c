#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  filename ;
struct TYPE_7__ {unsigned short port; } ;
struct TYPE_6__ {int /*<<< orphan*/ * socketdir; } ;
struct TYPE_5__ {unsigned short port; char* pgdata; int /*<<< orphan*/ * sockdir; int /*<<< orphan*/  major_version; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ ClusterInfo ;

/* Variables and functions */
 unsigned short DEF_PGUPORT ; 
 int GET_MAJOR_VERSION (int /*<<< orphan*/ ) ; 
 int LOCK_FILE_LINE_PORT ; 
 int LOCK_FILE_LINE_SOCKET_DIR ; 
 int MAXPGPATH ; 
 int Max (int,int) ; 
 int /*<<< orphan*/  PG_WARNING ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 TYPE_3__ old_cluster ; 
 int /*<<< orphan*/  pg_fatal (char*,...) ; 
 int /*<<< orphan*/  pg_log (int /*<<< orphan*/ ,char*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/ * pg_strdup (char*) ; 
 int /*<<< orphan*/  pg_strip_crlf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  sscanf (char*,char*,unsigned short*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 TYPE_2__ user_opts ; 

void
get_sock_dir(ClusterInfo *cluster, bool live_check)
{
#ifdef HAVE_UNIX_SOCKETS

	/*
	 * sockdir and port were added to postmaster.pid in PG 9.1. Pre-9.1 cannot
	 * process pg_ctl -w for sockets in non-default locations.
	 */
	if (GET_MAJOR_VERSION(cluster->major_version) >= 901)
	{
		if (!live_check)
			cluster->sockdir = user_opts.socketdir;
		else
		{
			/*
			 * If we are doing a live check, we will use the old cluster's
			 * Unix domain socket directory so we can connect to the live
			 * server.
			 */
			unsigned short orig_port = cluster->port;
			char		filename[MAXPGPATH],
						line[MAXPGPATH];
			FILE	   *fp;
			int			lineno;

			snprintf(filename, sizeof(filename), "%s/postmaster.pid",
					 cluster->pgdata);
			if ((fp = fopen(filename, "r")) == NULL)
				pg_fatal("could not open file \"%s\": %s\n",
						 filename, strerror(errno));

			for (lineno = 1;
				 lineno <= Max(LOCK_FILE_LINE_PORT, LOCK_FILE_LINE_SOCKET_DIR);
				 lineno++)
			{
				if (fgets(line, sizeof(line), fp) == NULL)
					pg_fatal("could not read line %d from file \"%s\": %s\n",
							 lineno, filename, strerror(errno));

				/* potentially overwrite user-supplied value */
				if (lineno == LOCK_FILE_LINE_PORT)
					sscanf(line, "%hu", &old_cluster.port);
				if (lineno == LOCK_FILE_LINE_SOCKET_DIR)
				{
					/* strip trailing newline and carriage return */
					cluster->sockdir = pg_strdup(line);
					(void) pg_strip_crlf(cluster->sockdir);
				}
			}
			fclose(fp);

			/* warn of port number correction */
			if (orig_port != DEF_PGUPORT && old_cluster.port != orig_port)
				pg_log(PG_WARNING, "user-supplied old port number %hu corrected to %hu\n",
					   orig_port, cluster->port);
		}
	}
	else

		/*
		 * Can't get sockdir and pg_ctl -w can't use a non-default, use
		 * default
		 */
		cluster->sockdir = NULL;
#else							/* !HAVE_UNIX_SOCKETS */
	cluster->sockdir = NULL;
#endif
}