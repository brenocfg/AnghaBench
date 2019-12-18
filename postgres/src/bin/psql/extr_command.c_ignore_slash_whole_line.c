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
typedef  int /*<<< orphan*/  PsqlScanState ;

/* Variables and functions */
 int /*<<< orphan*/  OT_WHOLE_LINE ; 
 int /*<<< orphan*/  free (char*) ; 
 char* psql_scan_slash_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ignore_slash_whole_line(PsqlScanState scan_state)
{
	char	   *arg = psql_scan_slash_option(scan_state,
											 OT_WHOLE_LINE, NULL, false);

	if (arg)
		free(arg);
}