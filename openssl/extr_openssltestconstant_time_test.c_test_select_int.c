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
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  constant_time_select_int (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int test_select_int(int a, int b)
{
    if (!TEST_int_eq(constant_time_select_int(CONSTTIME_TRUE, a, b), a))
        return 0;
    if (!TEST_int_eq(constant_time_select_int(CONSTTIME_FALSE, a, b), b))
        return 0;
    return 1;
}