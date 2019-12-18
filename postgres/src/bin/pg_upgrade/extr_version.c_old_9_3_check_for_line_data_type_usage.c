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
typedef  int /*<<< orphan*/  output_path ;
typedef  int /*<<< orphan*/  ClusterInfo ;

/* Variables and functions */
 int MAXPGPATH ; 
 int /*<<< orphan*/  PG_REPORT ; 
 scalar_t__ check_for_data_type_usage (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  check_ok () ; 
 int /*<<< orphan*/  pg_fatal (char*,char*) ; 
 int /*<<< orphan*/  pg_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  prep_status (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 

void
old_9_3_check_for_line_data_type_usage(ClusterInfo *cluster)
{
	char		output_path[MAXPGPATH];

	prep_status("Checking for incompatible \"line\" data type");

	snprintf(output_path, sizeof(output_path), "tables_using_line.txt");

	if (check_for_data_type_usage(cluster, "pg_catalog.line", output_path))
	{
		pg_log(PG_REPORT, "fatal\n");
		pg_fatal("Your installation contains the \"line\" data type in user tables.  This\n"
				 "data type changed its internal and input/output format between your old\n"
				 "and new clusters so this cluster cannot currently be upgraded.  You can\n"
				 "remove the problem tables and restart the upgrade.  A list of the problem\n"
				 "columns is in the file:\n"
				 "    %s\n\n", output_path);
	}
	else
		check_ok();
}