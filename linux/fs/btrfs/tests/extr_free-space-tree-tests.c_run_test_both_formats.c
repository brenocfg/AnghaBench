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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  test_func_t ;

/* Variables and functions */
 int run_test (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int run_test_both_formats(test_func_t test_func, u32 sectorsize,
				 u32 nodesize, u32 alignment)
{
	int test_ret = 0;
	int ret;

	ret = run_test(test_func, 0, sectorsize, nodesize, alignment);
	if (ret) {
		test_err(
	"%ps failed with extents, sectorsize=%u, nodesize=%u, alignment=%u",
			 test_func, sectorsize, nodesize, alignment);
		test_ret = ret;
	}

	ret = run_test(test_func, 1, sectorsize, nodesize, alignment);
	if (ret) {
		test_err(
	"%ps failed with bitmaps, sectorsize=%u, nodesize=%u, alignment=%u",
			 test_func, sectorsize, nodesize, alignment);
		test_ret = ret;
	}

	return test_ret;
}