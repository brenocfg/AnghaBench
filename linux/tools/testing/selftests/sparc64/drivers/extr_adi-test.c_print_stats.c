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
 int /*<<< orphan*/  DEBUG_PRINT_L1 (char*) ; 
 int /*<<< orphan*/  pread_stats ; 
 int /*<<< orphan*/  print_ustats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwrite_stats ; 
 int /*<<< orphan*/  read_stats ; 
 int /*<<< orphan*/  seek_stats ; 
 int /*<<< orphan*/  write_stats ; 

__attribute__((used)) static void print_stats(void)
{
	DEBUG_PRINT_L1("\nSyscall\tCall\tAvgTime\tAvgSize\n"
		       "\tCount\t(ticks)\t(bytes)\n"
		       "-------------------------------\n");

	print_ustats(&read_stats);
	print_ustats(&pread_stats);
	print_ustats(&write_stats);
	print_ustats(&pwrite_stats);
	print_ustats(&seek_stats);
}