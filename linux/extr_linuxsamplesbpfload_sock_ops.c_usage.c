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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void usage(char *pname)
{
	printf("USAGE:\n  %s [-l] <cg-path> <prog filename>\n", pname);
	printf("\tLoad and attach a sock_ops program to the specified "
	       "cgroup\n");
	printf("\tIf \"-l\" is used, the program will continue to run\n");
	printf("\tprinting the BPF log buffer\n");
	printf("\tIf the specified filename does not end in \".o\", it\n");
	printf("\tappends \"_kern.o\" to the name\n");
	printf("\n");
	printf("  %s -r <cg-path>\n", pname);
	printf("\tDetaches the currently attached sock_ops program\n");
	printf("\tfrom the specified cgroup\n");
	printf("\n");
	exit(1);
}