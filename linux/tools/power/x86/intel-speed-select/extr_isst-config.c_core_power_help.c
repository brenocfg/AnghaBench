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
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void core_power_help(void)
{
	printf("core-power:\tInterface that allows user to define per core/tile\n\
		priority.\n");
	printf("\nCommands : For feature=core-power\n");
	printf("\tinfo\n");
	printf("\tenable\n");
	printf("\tdisable\n");
	printf("\tconfig\n");
	printf("\tget-config\n");
	printf("\tassoc\n");
	printf("\tget-assoc\n");
}