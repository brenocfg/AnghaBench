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
	printf("Usage: %s [-d] [-D] <cg-path> <egress|ingress>\n", argv0);
	printf("	-d	Drop Traffic\n");
	printf("	-D	Detach filter, and exit\n");
	return EXIT_FAILURE;
}