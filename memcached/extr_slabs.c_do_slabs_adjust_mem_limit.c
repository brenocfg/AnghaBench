#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t maxbytes; } ;

/* Variables and functions */
 int /*<<< orphan*/ * mem_base ; 
 size_t mem_limit ; 
 int mem_limit_reached ; 
 int /*<<< orphan*/  memory_release () ; 
 TYPE_1__ settings ; 

__attribute__((used)) static bool do_slabs_adjust_mem_limit(size_t new_mem_limit) {
    /* Cannot adjust memory limit at runtime if prealloc'ed */
    if (mem_base != NULL)
        return false;
    settings.maxbytes = new_mem_limit;
    mem_limit = new_mem_limit;
    mem_limit_reached = false; /* Will reset on next alloc */
    memory_release(); /* free what might already be in the global pool */
    return true;
}