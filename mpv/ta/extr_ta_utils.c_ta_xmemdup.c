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
 void* ta_memdup (void*,void*,size_t) ; 
 int /*<<< orphan*/  ta_oom_b (int /*<<< orphan*/ ) ; 

void *ta_xmemdup(void *ta_parent, void *ptr, size_t size)
{
    void *new = ta_memdup(ta_parent, ptr, size);
    ta_oom_b(new || !ptr);
    return new;
}