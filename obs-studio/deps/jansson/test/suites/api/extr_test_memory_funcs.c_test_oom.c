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
 int /*<<< orphan*/  create_and_free_object_with_oom () ; 
 int /*<<< orphan*/  fail (char*) ; 
 scalar_t__ free_called ; 
 int /*<<< orphan*/  json_set_alloc_funcs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oom_free ; 
 int /*<<< orphan*/  oom_malloc ; 

__attribute__((used)) static void test_oom()
{
    free_called = 0;
    json_set_alloc_funcs(oom_malloc, oom_free);
    create_and_free_object_with_oom();

    if (free_called == 0)
        fail("Allocation with OOM failed");
}