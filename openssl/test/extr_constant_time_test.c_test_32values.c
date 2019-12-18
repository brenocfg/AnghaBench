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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 size_t OSSL_NELEM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_select_32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * test_values_32 ; 

__attribute__((used)) static int test_32values(int i)
{
    uint32_t e = test_values_32[i];
    size_t j;
    int ret = 1;

    for (j = 0; j < OSSL_NELEM(test_values_32); j++) {
        uint32_t f = test_values_32[j];

        if (!test_select_32(e, f))
            ret = 0;
    }
    return ret;
}