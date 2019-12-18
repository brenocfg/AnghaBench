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

/* Variables and functions */
 int /*<<< orphan*/  PG_REPORT ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_status (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stdout ; 

void
check_ok(void)
{
	/* all seems well */
	report_status(PG_REPORT, "ok");
	fflush(stdout);
}