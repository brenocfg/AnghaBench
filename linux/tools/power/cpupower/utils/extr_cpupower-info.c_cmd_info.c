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
struct TYPE_2__ {int caps; } ;

/* Variables and functions */
 int CPUPOWER_CAP_PERF_BIAS ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  PACKAGE ; 
 char* _ (char*) ; 
 unsigned int bitmask_first (int /*<<< orphan*/ ) ; 
 scalar_t__ bitmask_isallclear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmask_isbitset (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int bitmask_last (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmask_setbit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ cpupower_cpu_info ; 
 int /*<<< orphan*/  cpus_chosen ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int msr_intel_get_perf_bias (unsigned int) ; 
 int /*<<< orphan*/  print_wrong_arg_exit () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  run_as_root ; 
 int /*<<< orphan*/  set_opts ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int sysfs_is_cpu_online (unsigned int) ; 
 int /*<<< orphan*/  textdomain (int /*<<< orphan*/ ) ; 

int cmd_info(int argc, char **argv)
{
	extern char *optarg;
	extern int optind, opterr, optopt;
	unsigned int cpu;

	union {
		struct {
			int perf_bias:1;
		};
		int params;
	} params = {};
	int ret = 0;

	setlocale(LC_ALL, "");
	textdomain(PACKAGE);

	/* parameter parsing */
	while ((ret = getopt_long(argc, argv, "b", set_opts, NULL)) != -1) {
		switch (ret) {
		case 'b':
			if (params.perf_bias)
				print_wrong_arg_exit();
			params.perf_bias = 1;
			break;
		default:
			print_wrong_arg_exit();
		}
	};

	if (!params.params)
		params.params = 0x7;

	/* Default is: show output of CPU 0 only */
	if (bitmask_isallclear(cpus_chosen))
		bitmask_setbit(cpus_chosen, 0);

	/* Add more per cpu options here */
	if (!params.perf_bias)
		return ret;

	if (params.perf_bias) {
		if (!run_as_root) {
			params.perf_bias = 0;
			printf(_("Intel's performance bias setting needs root privileges\n"));
		} else if (!(cpupower_cpu_info.caps & CPUPOWER_CAP_PERF_BIAS)) {
			printf(_("System does not support Intel's performance"
				 " bias setting\n"));
			params.perf_bias = 0;
		}
	}

	/* loop over CPUs */
	for (cpu = bitmask_first(cpus_chosen);
	     cpu <= bitmask_last(cpus_chosen); cpu++) {

		if (!bitmask_isbitset(cpus_chosen, cpu))
			continue;

		printf(_("analyzing CPU %d:\n"), cpu);

		if (sysfs_is_cpu_online(cpu) != 1){
			printf(_(" *is offline\n"));
			continue;
		}

		if (params.perf_bias) {
			ret = msr_intel_get_perf_bias(cpu);
			if (ret < 0) {
				fprintf(stderr,
			_("Could not read perf-bias value[%d]\n"), ret);
				exit(EXIT_FAILURE);
			} else
				printf(_("perf-bias: %d\n"), ret);
		}
	}
	return 0;
}