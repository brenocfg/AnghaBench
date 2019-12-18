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

__attribute__((used)) static void pbf_help(void)
{
	printf("base-freq:\tEnables users to increase guaranteed base frequency\n\
		on certain cores (high priority cores) in exchange for lower\n\
		base frequency on remaining cores (low priority cores).\n");
	printf("\tcommand : info\n");
	printf("\tcommand : enable\n");
	printf("\tcommand : disable\n");
}