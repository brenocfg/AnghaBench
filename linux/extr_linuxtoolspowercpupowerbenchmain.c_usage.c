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

void usage()
{
	printf("usage: ./bench\n");
	printf("Options:\n");
	printf(" -l, --load=<long int>\t\tinitial load time in us\n");
	printf(" -s, --sleep=<long int>\t\tinitial sleep time in us\n");
	printf(" -x, --load-step=<long int>\ttime to be added to load time, in us\n");
	printf(" -y, --sleep-step=<long int>\ttime to be added to sleep time, in us\n");
	printf(" -c, --cpu=<cpu #>\t\t\tCPU Nr. to use, starting at 0\n");
	printf(" -p, --prio=<priority>\t\t\tscheduler priority, HIGH, LOW or DEFAULT\n");
	printf(" -g, --governor=<governor>\t\tcpufreq governor to test\n");
	printf(" -n, --cycles=<int>\t\t\tload/sleep cycles\n");
	printf(" -r, --rounds<int>\t\t\tload/sleep rounds\n");
	printf(" -f, --file=<configfile>\t\tconfig file to use\n");
	printf(" -o, --output=<dir>\t\t\toutput path. Filename will be OUTPUTPATH/benchmark_TIMESTAMP.log\n");
	printf(" -v, --verbose\t\t\t\tverbose output on/off\n");
	printf(" -h, --help\t\t\t\tPrint this help screen\n");
	exit(1);
}