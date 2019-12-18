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
 int /*<<< orphan*/  assert_int_equal (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
failing_test(void **state) {
    /* This tests fails to test that make check fails */
    assert_int_equal(0, 42);
}