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
typedef  int /*<<< orphan*/  zero ;

/* Variables and functions */
 int PAGE_SIZE ; 
 scalar_t__ __end_rodata ; 
 scalar_t__ __start_rodata ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  probe_kernel_write (void*,void*,int) ; 
 int rodata_test_data ; 

void rodata_test(void)
{
	unsigned long start, end;
	int zero = 0;

	/* test 1: read the value */
	/* If this test fails, some previous testrun has clobbered the state */
	if (!rodata_test_data) {
		pr_err("test 1 fails (start data)\n");
		return;
	}

	/* test 2: write to the variable; this should fault */
	if (!probe_kernel_write((void *)&rodata_test_data,
				(void *)&zero, sizeof(zero))) {
		pr_err("test data was not read only\n");
		return;
	}

	/* test 3: check the value hasn't changed */
	if (rodata_test_data == zero) {
		pr_err("test data was changed\n");
		return;
	}

	/* test 4: check if the rodata section is PAGE_SIZE aligned */
	start = (unsigned long)__start_rodata;
	end = (unsigned long)__end_rodata;
	if (start & (PAGE_SIZE - 1)) {
		pr_err("start of .rodata is not page size aligned\n");
		return;
	}
	if (end & (PAGE_SIZE - 1)) {
		pr_err("end of .rodata is not page size aligned\n");
		return;
	}

	pr_info("all tests were successful\n");
}