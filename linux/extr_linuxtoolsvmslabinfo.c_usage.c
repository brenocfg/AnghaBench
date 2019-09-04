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

__attribute__((used)) static void usage(void)
{
	printf("slabinfo 4/15/2011. (c) 2007 sgi/(c) 2011 Linux Foundation.\n\n"
		"slabinfo [-ahnpvtsz] [-d debugopts] [slab-regexp]\n"
		"-a|--aliases           Show aliases\n"
		"-A|--activity          Most active slabs first\n"
		"-d<options>|--debug=<options> Set/Clear Debug options\n"
		"-D|--display-active    Switch line format to activity\n"
		"-e|--empty             Show empty slabs\n"
		"-f|--first-alias       Show first alias\n"
		"-h|--help              Show usage information\n"
		"-i|--inverted          Inverted list\n"
		"-l|--slabs             Show slabs\n"
		"-n|--numa              Show NUMA information\n"
		"-o|--ops		Show kmem_cache_ops\n"
		"-s|--shrink            Shrink slabs\n"
		"-r|--report		Detailed report on single slabs\n"
		"-S|--Size              Sort by size\n"
		"-t|--tracking          Show alloc/free information\n"
		"-T|--Totals            Show summary information\n"
		"-v|--validate          Validate slabs\n"
		"-z|--zero              Include empty slabs\n"
		"-1|--1ref              Single reference\n"
		"-N|--lines=K           Show the first K slabs\n"
		"-L|--Loss              Sort by loss\n"
		"-X|--Xtotals           Show extended summary information\n"
		"-B|--Bytes             Show size in bytes\n"
		"-U|--Unreclaim		Show unreclaimable slabs only\n"
		"\nValid debug options (FZPUT may be combined)\n"
		"a / A          Switch on all debug options (=FZUP)\n"
		"-              Switch off all debug options\n"
		"f / F          Sanity Checks (SLAB_CONSISTENCY_CHECKS)\n"
		"z / Z          Redzoning\n"
		"p / P          Poisoning\n"
		"u / U          Tracking\n"
		"t / T          Tracing\n"
	);
}