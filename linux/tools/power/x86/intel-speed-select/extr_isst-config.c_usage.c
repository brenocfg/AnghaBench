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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void usage(void)
{
	printf("Intel(R) Speed Select Technology\n");
	printf("\nUsage:\n");
	printf("intel-speed-select [OPTIONS] FEATURE COMMAND COMMAND_ARGUMENTS\n");
	printf("\nUse this tool to enumerate and control the Intel Speed Select Technology features,\n");
	printf("\nFEATURE : [perf-profile|base-freq|turbo-freq|core-power]\n");
	printf("\nFor help on each feature, use -h|--help\n");
	printf("\tFor example:  intel-speed-select perf-profile -h\n");

	printf("\nFor additional help on each command for a feature, use --h|--help\n");
	printf("\tFor example:  intel-speed-select perf-profile get-lock-status -h\n");
	printf("\t\t This will print help for the command \"get-lock-status\" for the feature \"perf-profile\"\n");

	printf("\nOPTIONS\n");
	printf("\t[-c|--cpu] : logical cpu number\n");
	printf("\t\tDefault: Die scoped for all dies in the system with multiple dies/package\n");
	printf("\t\t\t Or Package scoped for all Packages when each package contains one die\n");
	printf("\t[-d|--debug] : Debug mode\n");
	printf("\t[-h|--help] : Print help\n");
	printf("\t[-i|--info] : Print platform information\n");
	printf("\t[-o|--out] : Output file\n");
	printf("\t\t\tDefault : stderr\n");
	printf("\t[-f|--format] : output format [json|text]. Default: text\n");
	printf("\t[-v|--version] : Print version\n");

	printf("\nResult format\n");
	printf("\tResult display uses a common format for each command:\n");
	printf("\tResults are formatted in text/JSON with\n");
	printf("\t\tPackage, Die, CPU, and command specific results.\n");
	exit(1);
}