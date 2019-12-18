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
struct TYPE_3__ {int /*<<< orphan*/  heap; } ;
typedef  TYPE_1__ vbscode_t ;

/* Variables and functions */
 void* heap_pool_alloc (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static inline void *compiler_alloc(vbscode_t *vbscode, size_t size)
{
    return heap_pool_alloc(&vbscode->heap, size);
}