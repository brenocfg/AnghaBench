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
 scalar_t__ INT_MAX ; 
 scalar_t__ SIZE_MAX ; 
 int /*<<< orphan*/  TEST_error (char*) ; 

__attribute__((used)) static int test_sanity_range(void)
{
    /* This isn't possible to check using the framework functions */
    if (SIZE_MAX < INT_MAX) {
        TEST_error("int must not be wider than size_t");
        return 0;
    }
    return 1;
}