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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int evswitch__fprintf_enoent(FILE *fp, const char *evtype, const char *evname)
{
	int printed = fprintf(fp, "ERROR: switch-%s event not found (%s)\n", evtype, evname);

	return printed += fprintf(fp, "HINT:  use 'perf evlist' to see the available event names\n");
}