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
 int /*<<< orphan*/  backtrace_test_irq () ; 
 int /*<<< orphan*/  backtrace_test_normal () ; 
 int /*<<< orphan*/  backtrace_test_saved () ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int backtrace_regression_test(void)
{
	pr_info("====[ backtrace testing ]===========\n");

	backtrace_test_normal();
	backtrace_test_irq();
	backtrace_test_saved();

	pr_info("====[ end of backtrace testing ]====\n");
	return 0;
}