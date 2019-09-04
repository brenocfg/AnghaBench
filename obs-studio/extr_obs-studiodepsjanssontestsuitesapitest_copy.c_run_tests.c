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
 int /*<<< orphan*/  test_copy_array () ; 
 int /*<<< orphan*/  test_copy_object () ; 
 int /*<<< orphan*/  test_copy_simple () ; 
 int /*<<< orphan*/  test_deep_copy_array () ; 
 int /*<<< orphan*/  test_deep_copy_object () ; 
 int /*<<< orphan*/  test_deep_copy_simple () ; 

__attribute__((used)) static void run_tests()
{
    test_copy_simple();
    test_deep_copy_simple();
    test_copy_array();
    test_deep_copy_array();
    test_copy_object();
    test_deep_copy_object();
}