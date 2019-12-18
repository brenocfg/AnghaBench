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
 char* cmdline ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 char* target ; 

__attribute__((used)) static void print_cmdline(void)
{
	printf("cmd_%s := %s\n\n", target, cmdline);
}