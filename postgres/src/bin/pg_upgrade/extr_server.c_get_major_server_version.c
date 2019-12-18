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
typedef  int /*<<< orphan*/  ver_filename ;
typedef  int uint32 ;
struct TYPE_3__ {char* pgdata; int /*<<< orphan*/  major_version_str; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ ClusterInfo ;

/* Variables and functions */
 int MAXPGPATH ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ fscanf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_fatal (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int sscanf (int /*<<< orphan*/ ,char*,int*,int*) ; 

uint32
get_major_server_version(ClusterInfo *cluster)
{
	FILE	   *version_fd;
	char		ver_filename[MAXPGPATH];
	int			v1 = 0,
				v2 = 0;

	snprintf(ver_filename, sizeof(ver_filename), "%s/PG_VERSION",
			 cluster->pgdata);
	if ((version_fd = fopen(ver_filename, "r")) == NULL)
		pg_fatal("could not open version file: %s\n", ver_filename);

	if (fscanf(version_fd, "%63s", cluster->major_version_str) == 0 ||
		sscanf(cluster->major_version_str, "%d.%d", &v1, &v2) < 1)
		pg_fatal("could not parse PG_VERSION file from %s\n", cluster->pgdata);

	fclose(version_fd);

	if (v1 < 10)
	{
		/* old style, e.g. 9.6.1 */
		return v1 * 10000 + v2 * 100;
	}
	else
	{
		/* new style, e.g. 10.1 */
		return v1 * 10000;
	}
}