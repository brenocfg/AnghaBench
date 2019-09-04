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
struct sysinfo {unsigned long totalram; unsigned long freeram; unsigned long bufferram; int /*<<< orphan*/  mem_unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  print (char const*) ; 
 int /*<<< orphan*/  print_k_value (char*,unsigned long,int /*<<< orphan*/ ) ; 
 int sysinfo (struct sysinfo*) ; 

void _start(void)
{
	int ccode;
	struct sysinfo info;
	unsigned long used;
	static const char *test_name = " get runtime memory use\n";

	print("TAP version 13\n");
	print("# Testing system size.\n");

	ccode = sysinfo(&info);
	if (ccode < 0) {
		print("not ok 1");
		print(test_name);
		print(" ---\n reason: \"could not get sysinfo\"\n ...\n");
		_exit(ccode);
	}
	print("ok 1");
	print(test_name);

	/* ignore cache complexities for now */
	used = info.totalram - info.freeram - info.bufferram;
	print("# System runtime memory report (units in Kilobytes):\n");
	print(" ---\n");
	print_k_value(" Total:  ", info.totalram, info.mem_unit);
	print_k_value(" Free:   ", info.freeram, info.mem_unit);
	print_k_value(" Buffer: ", info.bufferram, info.mem_unit);
	print_k_value(" In use: ", used, info.mem_unit);
	print(" ...\n");
	print("1..1\n");

	_exit(0);
}