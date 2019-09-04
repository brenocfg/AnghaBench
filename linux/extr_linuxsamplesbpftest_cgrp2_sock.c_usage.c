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
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int usage(const char *argv0)
{
	printf("Usage:\n");
	printf("  Attach a program\n");
	printf("  %s -b bind-to-dev -m mark -p prio cg-path\n", argv0);
	printf("\n");
	printf("  Detach a program\n");
	printf("  %s -d cg-path\n", argv0);
	printf("\n");
	printf("  Show inherited socket settings (mark, priority, and device)\n");
	printf("  %s [-6]\n", argv0);
	return EXIT_FAILURE;
}