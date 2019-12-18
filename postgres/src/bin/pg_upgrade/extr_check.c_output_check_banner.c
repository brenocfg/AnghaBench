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
 int /*<<< orphan*/  pg_log (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ user_opts ; 

void
output_check_banner(bool live_check)
{
	if (user_opts.check && live_check)
	{
		pg_log(PG_REPORT,
			   "Performing Consistency Checks on Old Live Server\n"
			   "------------------------------------------------\n");
	}
	else
	{
		pg_log(PG_REPORT,
			   "Performing Consistency Checks\n"
			   "-----------------------------\n");
	}
}