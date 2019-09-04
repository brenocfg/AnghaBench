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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hugetlb_testcases ; 
 int run_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  supported_arch () ; 
 int /*<<< orphan*/  testcases ; 

int main(int argc, char **argv)
{
	int ret;

	if (!supported_arch())
		return 0;

	ret = run_test(testcases, ARRAY_SIZE(testcases));
	if (argc == 2 && !strcmp(argv[1], "--run-hugetlb"))
		ret = run_test(hugetlb_testcases, ARRAY_SIZE(hugetlb_testcases));
	return ret;
}