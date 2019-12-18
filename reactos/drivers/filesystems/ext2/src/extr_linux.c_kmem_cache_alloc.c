#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  acount; int /*<<< orphan*/  count; int /*<<< orphan*/  la; } ;
typedef  TYPE_1__ kmem_cache_t ;
typedef  void* PVOID ;

/* Variables and functions */
 void* ExAllocateFromNPagedLookasideList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

void* kmem_cache_alloc(kmem_cache_t *kc, int flags)
{
    PVOID  ptr = NULL;
    ptr = ExAllocateFromNPagedLookasideList(&(kc->la));
    if (ptr) {
        atomic_inc(&kc->count);
        atomic_inc(&kc->acount);
    }
    return ptr;
}