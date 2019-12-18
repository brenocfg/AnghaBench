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
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_size_t_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  constant_time_eq_s (size_t,size_t) ; 

__attribute__((used)) static int test_eq_s(size_t a, size_t b)
{
    if (a == b && !TEST_size_t_eq(constant_time_eq_s(a, b), CONSTTIME_TRUE_S))
        return 0;
    if (a != b && !TEST_int_eq(constant_time_eq_s(a, b), CONSTTIME_FALSE_S))
        return 0;
    return 1;
}