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
 int /*<<< orphan*/  dummy_dtor ; 
 void* ta_alloc_size (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ta_free (void*) ; 
 int /*<<< orphan*/  ta_set_destructor (void*,int /*<<< orphan*/ ) ; 

void *ta_new_context(void *ta_parent)
{
    void *new = ta_alloc_size(ta_parent, 0);
    // Force it to allocate an extended header.
    if (!ta_set_destructor(new, dummy_dtor)) {
        ta_free(new);
        new = NULL;
    }
    return new;
}