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
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void Usage(void)
{
	printf("This program loads a cgroup skb BPF program to enforce\n"
	       "cgroup output (egress) bandwidth limits.\n\n"
	       "USAGE: hbm [-o] [-d]  [-l] [-n <id>] [--no_cn] [-r <rate>]\n"
	       "           [-s] [-t <secs>] [-w] [-h] [prog]\n"
	       "  Where:\n"
	       "    -o         indicates egress direction (default)\n"
	       "    -d         print BPF trace debug buffer\n"
	       "    --edt      use fq's Earliest Departure Time\n"
	       "    -l         also limit flows using loopback\n"
	       "    -n <#>     to create cgroup \"/hbm#\" and attach prog\n"
	       "               Default is /hbm1\n"
	       "    --no_cn    disable CN notifications\n"
	       "    -r <rate>  Rate in Mbps\n"
	       "    -s         Update HBM stats\n"
	       "    -t <time>  Exit after specified seconds (default is 0)\n"
	       "    -w	       Work conserving flag. cgroup can increase\n"
	       "               bandwidth beyond the rate limit specified\n"
	       "               while there is available bandwidth. Current\n"
	       "               implementation assumes there is only eth0\n"
	       "               but can be extended to support multiple NICs\n"
	       "    -h         print this info\n"
	       "    prog       BPF program file name. Name defaults to\n"
	       "                 hbm_out_kern.o\n");
}