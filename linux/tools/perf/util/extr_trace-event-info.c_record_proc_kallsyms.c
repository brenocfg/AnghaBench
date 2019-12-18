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
 int EIO ; 
 int /*<<< orphan*/  output_fd ; 
 int write (int /*<<< orphan*/ ,unsigned long long*,int) ; 

__attribute__((used)) static int record_proc_kallsyms(void)
{
	unsigned long long size = 0;
	/*
	 * Just to keep older perf.data file parsers happy, record a zero
	 * sized kallsyms file, i.e. do the same thing that was done when
	 * /proc/kallsyms (or something specified via --kallsyms, in a
	 * different path) couldn't be read.
	 */
	return write(output_fd, &size, 4) != 4 ? -EIO : 0;
}