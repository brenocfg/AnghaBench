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
 int /*<<< orphan*/  test_circular () ; 
 int /*<<< orphan*/  test_clear () ; 
 int /*<<< orphan*/  test_conditional_updates () ; 
 int /*<<< orphan*/  test_iterators () ; 
 int /*<<< orphan*/  test_misc () ; 
 int /*<<< orphan*/  test_object_foreach () ; 
 int /*<<< orphan*/  test_object_foreach_safe () ; 
 int /*<<< orphan*/  test_preserve_order () ; 
 int /*<<< orphan*/  test_set_many_keys () ; 
 int /*<<< orphan*/  test_set_nocheck () ; 
 int /*<<< orphan*/  test_update () ; 

__attribute__((used)) static void run_tests()
{
    test_misc();
    test_clear();
    test_update();
    test_set_many_keys();
    test_conditional_updates();
    test_circular();
    test_set_nocheck();
    test_iterators();
    test_preserve_order();
    test_object_foreach();
    test_object_foreach_safe();
}