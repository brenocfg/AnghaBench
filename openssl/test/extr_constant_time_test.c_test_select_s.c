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
 int /*<<< orphan*/  TEST_uint_eq (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  constant_time_select_s (int /*<<< orphan*/ ,size_t,size_t) ; 

__attribute__((used)) static int test_select_s(size_t a, size_t b)
{
    if (!TEST_uint_eq(constant_time_select_s(CONSTTIME_TRUE_S, a, b), a))
        return 0;
    if (!TEST_uint_eq(constant_time_select_s(CONSTTIME_FALSE_S, a, b), b))
        return 0;
    return 1;
}