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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONSTTIME_FALSE_32 ; 
 int /*<<< orphan*/  CONSTTIME_TRUE_32 ; 
 int /*<<< orphan*/  TEST_true (int) ; 
 scalar_t__ constant_time_select_32 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int test_select_32(uint32_t a, uint32_t b)
{
    if (!TEST_true(constant_time_select_32(CONSTTIME_TRUE_32, a, b) == a))
        return 0;
    if (!TEST_true(constant_time_select_32(CONSTTIME_FALSE_32, a, b) == b))
        return 0;
    return 1;
}