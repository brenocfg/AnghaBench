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
 int /*<<< orphan*/  OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_uint_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_values ; 
 int /*<<< orphan*/  test_values_s ; 

__attribute__((used)) static int test_sizeofs(void)
{
    if (!TEST_uint_eq(OSSL_NELEM(test_values), OSSL_NELEM(test_values_s)))
        return 0;
    return 1;
}