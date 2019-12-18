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
 void* coro_malloc_full (struct coro*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free ; 

inline void *coro_malloc(struct coro *coro, size_t size)
{
    return coro_malloc_full(coro, size, free);
}