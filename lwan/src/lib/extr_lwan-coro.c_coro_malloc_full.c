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
struct coro {int dummy; } ;

/* Variables and functions */
 scalar_t__ LIKELY (void*) ; 
 int /*<<< orphan*/  coro_defer (struct coro*,void (*) (void*),void*) ; 
 void* malloc (size_t) ; 

void *coro_malloc_full(struct coro *coro,
                       size_t size,
                       void (*destroy_func)(void *data))
{
    void *ptr = malloc(size);

    if (LIKELY(ptr))
        coro_defer(coro, destroy_func, ptr);

    return ptr;
}