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
struct TYPE_2__ {scalar_t__ check; } ;

/* Variables and functions */
 int /*<<< orphan*/  PG_REPORT ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stop_postmaster (int) ; 
 TYPE_1__ user_opts ; 

void
report_clusters_compatible(void)
{
	if (user_opts.check)
	{
		pg_log(PG_REPORT, "\n*Clusters are compatible*\n");
		/* stops new cluster */
		stop_postmaster(false);
		exit(0);
	}

	pg_log(PG_REPORT, "\n"
		   "If pg_upgrade fails after this point, you must re-initdb the\n"
		   "new cluster before continuing.\n");
}