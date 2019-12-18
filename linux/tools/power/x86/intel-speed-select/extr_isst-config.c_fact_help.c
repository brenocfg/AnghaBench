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

__attribute__((used)) static void fact_help(void)
{
	printf("turbo-freq:\tEnables the ability to set different turbo ratio\n\
		limits to cores based on priority.\n");
	printf("\nCommand: For feature=turbo-freq\n");
	printf("\tcommand : info\n");
	printf("\tcommand : enable\n");
	printf("\tcommand : disable\n");
}