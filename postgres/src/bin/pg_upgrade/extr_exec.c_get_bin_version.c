#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmd_output ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_3__ {char* bindir; int bin_version; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ ClusterInfo ;

/* Variables and functions */
 int MAXPGPATH ; 
 int MAX_STRING ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_fatal (char*,char*,...) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int sscanf (char*,char*,int*,int*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_bin_version(ClusterInfo *cluster)
{
	char		cmd[MAXPGPATH],
				cmd_output[MAX_STRING];
	FILE	   *output;
	int			v1 = 0,
				v2 = 0;

	snprintf(cmd, sizeof(cmd), "\"%s/pg_ctl\" --version", cluster->bindir);

	if ((output = popen(cmd, "r")) == NULL ||
		fgets(cmd_output, sizeof(cmd_output), output) == NULL)
		pg_fatal("could not get pg_ctl version data using %s: %s\n",
				 cmd, strerror(errno));

	pclose(output);

	if (sscanf(cmd_output, "%*s %*s %d.%d", &v1, &v2) < 1)
		pg_fatal("could not get pg_ctl version output from %s\n", cmd);

	if (v1 < 10)
	{
		/* old style, e.g. 9.6.1 */
		cluster->bin_version = v1 * 10000 + v2 * 100;
	}
	else
	{
		/* new style, e.g. 10.1 */
		cluster->bin_version = v1 * 10000;
	}
}