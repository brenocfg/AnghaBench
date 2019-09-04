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
 int KDB_ARGCOUNT ; 
 int KDB_BADINT ; 
 long NR_CPUS ; 
 long RING_BUFFER_ALL_CPUS ; 
 int /*<<< orphan*/  cpu_online (long) ; 
 int /*<<< orphan*/  ftrace_dump_buf (int,long) ; 
 int /*<<< orphan*/  kdb_trap_printk ; 
 void* simple_strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kdb_ftdump(int argc, const char **argv)
{
	int skip_lines = 0;
	long cpu_file;
	char *cp;

	if (argc > 2)
		return KDB_ARGCOUNT;

	if (argc) {
		skip_lines = simple_strtol(argv[1], &cp, 0);
		if (*cp)
			skip_lines = 0;
	}

	if (argc == 2) {
		cpu_file = simple_strtol(argv[2], &cp, 0);
		if (*cp || cpu_file >= NR_CPUS || cpu_file < 0 ||
		    !cpu_online(cpu_file))
			return KDB_BADINT;
	} else {
		cpu_file = RING_BUFFER_ALL_CPUS;
	}

	kdb_trap_printk++;
	ftrace_dump_buf(skip_lines, cpu_file);
	kdb_trap_printk--;

	return 0;
}