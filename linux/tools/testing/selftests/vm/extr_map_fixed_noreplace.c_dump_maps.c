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
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int getpid () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  system (char*) ; 

__attribute__((used)) static void dump_maps(void)
{
	char cmd[32];

	snprintf(cmd, sizeof(cmd), "cat /proc/%d/maps", getpid());
	system(cmd);
}