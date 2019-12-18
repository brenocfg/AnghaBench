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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ OSSL_NELEM (scalar_t__*) ; 
 int /*<<< orphan*/  TEST_info (char*,int,int) ; 
 int /*<<< orphan*/  constant_time_lt_64 ; 
 int /*<<< orphan*/  test_binary_op_64 (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  test_select_64 (scalar_t__,scalar_t__) ; 
 scalar_t__* test_values_64 ; 

__attribute__((used)) static int test_64values(int i)
{
    uint64_t g = test_values_64[i];
    int j, ret = 1;

    for (j = i + 1; j < (int)OSSL_NELEM(test_values_64); j++) {
        uint64_t h = test_values_64[j];

        if (!test_binary_op_64(&constant_time_lt_64, "constant_time_lt_64",
                               g, h, g < h)
                || !test_select_64(g, h)) {
            TEST_info("test_64values failed i=%d j=%d", i, j);
            ret = 0;
        }
    }
    return ret;
}