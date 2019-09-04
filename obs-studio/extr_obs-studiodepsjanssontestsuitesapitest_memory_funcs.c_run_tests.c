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
 int /*<<< orphan*/  test_oom () ; 
 int /*<<< orphan*/  test_secure_funcs () ; 
 int /*<<< orphan*/  test_simple () ; 

__attribute__((used)) static void run_tests()
{
    test_simple();
    test_secure_funcs();
    test_oom();
}