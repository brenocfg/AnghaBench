#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  cmd_output ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_4__ {char* pgconfig; char* pgdata; char* bindir; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ ClusterInfo ;

/* Variables and functions */
 int MAXPGPATH ; 
 int MAX_STRING ; 
 int /*<<< orphan*/  check_ok () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 TYPE_1__ old_cluster ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_fatal (char*,char*,int /*<<< orphan*/ ) ; 
 void* pg_strdup (char*) ; 
 int /*<<< orphan*/  pg_strip_crlf (char*) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  prep_status (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void
adjust_data_dir(ClusterInfo *cluster)
{
	char		filename[MAXPGPATH];
	char		cmd[MAXPGPATH],
				cmd_output[MAX_STRING];
	FILE	   *fp,
			   *output;

	/* Initially assume config dir and data dir are the same */
	cluster->pgconfig = pg_strdup(cluster->pgdata);

	/* If there is no postgresql.conf, it can't be a config-only dir */
	snprintf(filename, sizeof(filename), "%s/postgresql.conf", cluster->pgconfig);
	if ((fp = fopen(filename, "r")) == NULL)
		return;
	fclose(fp);

	/* If PG_VERSION exists, it can't be a config-only dir */
	snprintf(filename, sizeof(filename), "%s/PG_VERSION", cluster->pgconfig);
	if ((fp = fopen(filename, "r")) != NULL)
	{
		fclose(fp);
		return;
	}

	/* Must be a configuration directory, so find the real data directory. */

	if (cluster == &old_cluster)
		prep_status("Finding the real data directory for the source cluster");
	else
		prep_status("Finding the real data directory for the target cluster");

	/*
	 * We don't have a data directory yet, so we can't check the PG version,
	 * so this might fail --- only works for PG 9.2+.   If this fails,
	 * pg_upgrade will fail anyway because the data files will not be found.
	 */
	snprintf(cmd, sizeof(cmd), "\"%s/postgres\" -D \"%s\" -C data_directory",
			 cluster->bindir, cluster->pgconfig);

	if ((output = popen(cmd, "r")) == NULL ||
		fgets(cmd_output, sizeof(cmd_output), output) == NULL)
		pg_fatal("could not get data directory using %s: %s\n",
				 cmd, strerror(errno));

	pclose(output);

	/* strip trailing newline and carriage return */
	(void) pg_strip_crlf(cmd_output);

	cluster->pgdata = pg_strdup(cmd_output);

	check_ok();
}