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
 int /*<<< orphan*/  PERF_COLOR_GREEN ; 
 int /*<<< orphan*/  PERF_COLOR_RED ; 
 int /*<<< orphan*/  color_fprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void on_off_print(const char *status)
{
	printf("[ ");

	if (!strcmp(status, "OFF"))
		color_fprintf(stdout, PERF_COLOR_RED, "%-3s", status);
	else
		color_fprintf(stdout, PERF_COLOR_GREEN, "%-3s", status);

	printf(" ]");
}