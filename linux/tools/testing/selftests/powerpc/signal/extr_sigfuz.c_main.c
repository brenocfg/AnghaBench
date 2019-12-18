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
 int /*<<< orphan*/  ARG_COMPLETE ; 
 int /*<<< orphan*/  ARG_FOREVER ; 
 int /*<<< orphan*/  ARG_MESS_WITH_MSR_AT ; 
 int /*<<< orphan*/  ARG_MESS_WITH_TM_AT ; 
 int /*<<< orphan*/  ARG_MESS_WITH_TM_BEFORE ; 
 int /*<<< orphan*/  args ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int count_max ; 
 int getopt (int,char**,char*) ; 
 int nthread ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  show_help (char*) ; 
 int /*<<< orphan*/  signal_fuzzer ; 
 int /*<<< orphan*/  test_harness (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_harness_set_timeout (int) ; 

int main(int argc, char **argv)
{
	int opt;

	while ((opt = getopt(argc, argv, "bamxt:fi:h")) != -1) {
		if (opt == 'b') {
			printf("Mess with TM before signal\n");
			args |= ARG_MESS_WITH_TM_BEFORE;
		} else if (opt == 'a') {
			printf("Mess with TM at signal handler\n");
			args |= ARG_MESS_WITH_TM_AT;
		} else if (opt == 'm') {
			printf("Mess with MSR[TS] bits in mcontext\n");
			args |= ARG_MESS_WITH_MSR_AT;
		} else if (opt == 'x') {
			printf("Running with all options enabled\n");
			args |= ARG_COMPLETE;
		} else if (opt == 't') {
			nthread = atoi(optarg);
			printf("Threads = %d\n", nthread);
		} else if (opt == 'f') {
			args |= ARG_FOREVER;
			printf("Press ^C to stop\n");
			test_harness_set_timeout(-1);
		} else if (opt == 'i') {
			count_max = atoi(optarg);
			printf("Running for %d interactions\n", count_max);
		} else if (opt == 'h') {
			show_help(argv[0]);
		}
	}

	/* Default test suite */
	if (!args)
		args = ARG_COMPLETE;

	test_harness(signal_fuzzer, "signal_fuzzer");
}