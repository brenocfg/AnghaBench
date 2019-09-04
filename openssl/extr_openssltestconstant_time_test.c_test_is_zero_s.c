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
 int /*<<< orphan*/  CONSTTIME_FALSE_S ; 
 int /*<<< orphan*/  CONSTTIME_TRUE_S ; 
 int /*<<< orphan*/  TEST_size_t_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_uint_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  constant_time_is_zero_s (size_t) ; 
 size_t* test_values_s ; 

__attribute__((used)) static int test_is_zero_s(int i)
{
    size_t a = test_values_s[i];

    if (a == 0 && !TEST_size_t_eq(constant_time_is_zero_s(a), CONSTTIME_TRUE_S))
        return 0;
    if (a != 0 && !TEST_uint_eq(constant_time_is_zero_s(a), CONSTTIME_FALSE_S))
        return 0;
    return 1;
}