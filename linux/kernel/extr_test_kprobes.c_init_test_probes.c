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
 scalar_t__ div_factor ; 
 scalar_t__ errors ; 
 scalar_t__ handler_errors ; 
 int /*<<< orphan*/  kprobe_target ; 
 int /*<<< orphan*/  kprobe_target2 ; 
 int /*<<< orphan*/  num_tests ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ prandom_u32 () ; 
 scalar_t__ rand1 ; 
 int /*<<< orphan*/  target ; 
 int /*<<< orphan*/  target2 ; 
 int test_kprobe () ; 
 int test_kprobes () ; 
 int test_kretprobe () ; 
 int test_kretprobes () ; 

int init_test_probes(void)
{
	int ret;

	target = kprobe_target;
	target2 = kprobe_target2;

	do {
		rand1 = prandom_u32();
	} while (rand1 <= div_factor);

	pr_info("started\n");
	num_tests++;
	ret = test_kprobe();
	if (ret < 0)
		errors++;

	num_tests++;
	ret = test_kprobes();
	if (ret < 0)
		errors++;

#ifdef CONFIG_KRETPROBES
	num_tests++;
	ret = test_kretprobe();
	if (ret < 0)
		errors++;

	num_tests++;
	ret = test_kretprobes();
	if (ret < 0)
		errors++;
#endif /* CONFIG_KRETPROBES */

	if (errors)
		pr_err("BUG: %d out of %d tests failed\n", errors, num_tests);
	else if (handler_errors)
		pr_err("BUG: %d error(s) running handlers\n", handler_errors);
	else
		pr_info("passed successfully\n");

	return 0;
}