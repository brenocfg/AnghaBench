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
 int /*<<< orphan*/  test_array_foreach () ; 
 int /*<<< orphan*/  test_circular () ; 
 int /*<<< orphan*/  test_clear () ; 
 int /*<<< orphan*/  test_extend () ; 
 int /*<<< orphan*/  test_insert () ; 
 int /*<<< orphan*/  test_misc () ; 
 int /*<<< orphan*/  test_remove () ; 

__attribute__((used)) static void run_tests()
{
    test_misc();
    test_insert();
    test_remove();
    test_clear();
    test_extend();
    test_circular();
    test_array_foreach();
}