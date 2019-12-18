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
 void* ta_realloc_size (void*,void*,size_t) ; 

void *ta_xrealloc_size(void *ta_parent, void *ptr, size_t size)
{
    ptr = ta_realloc_size(ta_parent, ptr, size);
    ta_oom_b(ptr || !size);
    return ptr;
}