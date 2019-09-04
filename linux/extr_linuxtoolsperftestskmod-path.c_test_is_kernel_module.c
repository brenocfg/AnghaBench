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
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,int) ; 
 int /*<<< orphan*/  is_kernel_module (char const*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*,int,char*) ; 

__attribute__((used)) static int test_is_kernel_module(const char *path, int cpumode, bool expect)
{
	TEST_ASSERT_VAL("is_kernel_module",
			(!!is_kernel_module(path, cpumode)) == (!!expect));
	pr_debug("%s (cpumode: %d) - is_kernel_module: %s\n",
			path, cpumode, expect ? "true" : "false");
	return 0;
}