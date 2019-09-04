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
struct perf_mem {int operation; scalar_t__ phys_addr; scalar_t__ dump_raw; } ;

/* Variables and functions */
 int MEM_OPERATION_LOAD ; 
 char** calloc (int,int) ; 
 int cmd_report (int,char const**) ; 
 int /*<<< orphan*/  free (char const**) ; 
 int report_raw_events (struct perf_mem*) ; 

__attribute__((used)) static int report_events(int argc, const char **argv, struct perf_mem *mem)
{
	const char **rep_argv;
	int ret, i = 0, j, rep_argc;

	if (mem->dump_raw)
		return report_raw_events(mem);

	rep_argc = argc + 3;
	rep_argv = calloc(rep_argc + 1, sizeof(char *));
	if (!rep_argv)
		return -1;

	rep_argv[i++] = "report";
	rep_argv[i++] = "--mem-mode";
	rep_argv[i++] = "-n"; /* display number of samples */

	/*
	 * there is no weight (cost) associated with stores, so don't print
	 * the column
	 */
	if (!(mem->operation & MEM_OPERATION_LOAD)) {
		if (mem->phys_addr)
			rep_argv[i++] = "--sort=mem,sym,dso,symbol_daddr,"
					"dso_daddr,tlb,locked,phys_daddr";
		else
			rep_argv[i++] = "--sort=mem,sym,dso,symbol_daddr,"
					"dso_daddr,tlb,locked";
	} else if (mem->phys_addr)
		rep_argv[i++] = "--sort=local_weight,mem,sym,dso,symbol_daddr,"
				"dso_daddr,snoop,tlb,locked,phys_daddr";

	for (j = 1; j < argc; j++, i++)
		rep_argv[i] = argv[j];

	ret = cmd_report(i, rep_argv);
	free(rep_argv);
	return ret;
}