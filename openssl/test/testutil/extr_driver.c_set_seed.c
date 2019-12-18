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
 int seed ; 
 int /*<<< orphan*/  subtest_level () ; 
 int /*<<< orphan*/  test_flush_stdout () ; 
 int /*<<< orphan*/  test_printf_stdout (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  test_random_seed (int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_seed(int s)
{
    seed = s;
    if (seed <= 0)
        seed = (int)time(NULL);
    test_printf_stdout("%*s# RAND SEED %d\n", subtest_level(), "", seed);
    test_flush_stdout();
    test_random_seed(seed);
}