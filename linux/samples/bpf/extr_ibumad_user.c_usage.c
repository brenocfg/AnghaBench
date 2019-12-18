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
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void usage(char *cmd)
{
	printf("eBPF test program to count packets from various IP addresses\n"
		"Usage: %s <options>\n"
		"       --help,   -h  this menu\n"
		"       --delay,  -d  <delay>  wait <delay> sec between prints [1 - 1000000]\n"
		, cmd
		);
}