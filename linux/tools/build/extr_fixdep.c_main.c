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
 char* cmdline ; 
 char* depfile ; 
 int /*<<< orphan*/  print_cmdline () ; 
 int /*<<< orphan*/  print_deps () ; 
 char* target ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char **argv)
{
	if (argc != 4)
		usage();

	depfile = argv[1];
	target  = argv[2];
	cmdline = argv[3];

	print_cmdline();
	print_deps();

	return 0;
}