#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  enter_kgdb; } ;

/* Variables and functions */
 unsigned long CONFIG_NR_CPUS ; 
 int KDB_ARGCOUNT ; 
 int KDB_BADCPUNUM ; 
 int KDB_CMD_CPU ; 
 unsigned long dbg_switch_cpu ; 
 int /*<<< orphan*/  kdb_cpu_status () ; 
 int kdbgetularg (char const*,unsigned long*) ; 
 TYPE_1__* kgdb_info ; 

__attribute__((used)) static int kdb_cpu(int argc, const char **argv)
{
	unsigned long cpunum;
	int diag;

	if (argc == 0) {
		kdb_cpu_status();
		return 0;
	}

	if (argc != 1)
		return KDB_ARGCOUNT;

	diag = kdbgetularg(argv[1], &cpunum);
	if (diag)
		return diag;

	/*
	 * Validate cpunum
	 */
	if ((cpunum >= CONFIG_NR_CPUS) || !kgdb_info[cpunum].enter_kgdb)
		return KDB_BADCPUNUM;

	dbg_switch_cpu = cpunum;

	/*
	 * Switch to other cpu
	 */
	return KDB_CMD_CPU;
}