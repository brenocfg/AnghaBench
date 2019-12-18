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
 int /*<<< orphan*/  test_l4lb (char const*) ; 

void test_l4lb_all(void)
{
	const char *file1 = "./test_l4lb.o";
	const char *file2 = "./test_l4lb_noinline.o";

	test_l4lb(file1);
	test_l4lb(file2);
}