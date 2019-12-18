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
 size_t MAX_INCLUDES ; 
 int /*<<< orphan*/  assert (int) ; 
 int* cu_include_stack ; 
 size_t cu_include_stk_idx ; 

__attribute__((used)) static int stabs_add_include(int idx)
{
    if (idx < 0) return -1;
    cu_include_stk_idx++;

    /* if this happens, just bump MAX_INCLUDES */
    /* we could also handle this as another dynarray */
    assert(cu_include_stk_idx < MAX_INCLUDES);
    cu_include_stack[cu_include_stk_idx] = idx;
    return cu_include_stk_idx;
}