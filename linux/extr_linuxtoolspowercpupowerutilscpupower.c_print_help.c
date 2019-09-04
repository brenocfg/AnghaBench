#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* cmd; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 char* _ (char*) ; 
 TYPE_1__* commands ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void print_help(void)
{
	unsigned int i;

#ifdef DEBUG
	printf(_("Usage:\tcpupower [-d|--debug] [-c|--cpu cpulist ] <command> [<args>]\n"));
#else
	printf(_("Usage:\tcpupower [-c|--cpu cpulist ] <command> [<args>]\n"));
#endif
	printf(_("Supported commands are:\n"));
	for (i = 0; i < ARRAY_SIZE(commands); i++)
		printf("\t%s\n", commands[i].cmd);
	printf(_("\nNot all commands can make use of the -c cpulist option.\n"));
	printf(_("\nUse 'cpupower help <command>' for getting help for above commands.\n"));
}