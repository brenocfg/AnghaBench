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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 void* ta_alloc_size (void*,size_t) ; 

void *ta_memdup(void *ta_parent, void *ptr, size_t size)
{
    if (!ptr) {
        assert(!size);
        return NULL;
    }
    void *res = ta_alloc_size(ta_parent, size);
    if (!res)
        return NULL;
    memcpy(res, ptr, size);
    return res;
}