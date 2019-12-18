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
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void usage(const char *cmd)
{
	printf("USAGE: %s [-i num_progs] [-h]\n", cmd);
	printf("       -i num_progs      # number of progs of the test\n");
	printf("       -h                # help\n");
}