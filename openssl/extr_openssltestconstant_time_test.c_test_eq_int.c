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
 int /*<<< orphan*/  CONSTTIME_FALSE ; 
 int /*<<< orphan*/  CONSTTIME_TRUE ; 
 int /*<<< orphan*/  TEST_uint_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  constant_time_eq_int (int,int) ; 

__attribute__((used)) static int test_eq_int(int a, int b)
{
    if (a == b && !TEST_uint_eq(constant_time_eq_int(a, b), CONSTTIME_TRUE))
        return 0;
    if (a != b && !TEST_uint_eq(constant_time_eq_int(a, b), CONSTTIME_FALSE))
        return 0;
    return 1;
}