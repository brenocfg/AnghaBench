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
 int /*<<< orphan*/  ta_oom_b (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ta_set_parent (void*,void*) ; 

void *ta_xsteal_(void *ta_parent, void *ptr)
{
    ta_oom_b(ta_set_parent(ptr, ta_parent));
    return ptr;
}