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
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 

__attribute__((used)) static void do_error(char *msg, bool errno_flag)
{
	if (errno_flag)
		printf("ERROR: %s, errno: %d\n", msg, errno);
	else
		printf("ERROR: %s\n", msg);
	exit(1);
}