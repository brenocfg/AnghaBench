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
 int TEST_skip (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_skip_null(void)
{
    /*
     * This is not a recommended way of skipping a test, a reason or
     * description should be included.
     */
    return TEST_skip(NULL);
}