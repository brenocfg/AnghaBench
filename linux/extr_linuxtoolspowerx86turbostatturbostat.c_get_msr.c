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
typedef  int ssize_t ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*,int,unsigned long long) ; 
 int /*<<< orphan*/  get_msr_fd (int) ; 
 int pread (int /*<<< orphan*/ ,unsigned long long*,int,scalar_t__) ; 

int get_msr(int cpu, off_t offset, unsigned long long *msr)
{
	ssize_t retval;

	retval = pread(get_msr_fd(cpu), msr, sizeof(*msr), offset);

	if (retval != sizeof *msr)
		err(-1, "cpu%d: msr offset 0x%llx read failed", cpu, (unsigned long long)offset);

	return 0;
}