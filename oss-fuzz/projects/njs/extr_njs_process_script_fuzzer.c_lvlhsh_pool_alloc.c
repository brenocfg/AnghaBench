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
typedef  int /*<<< orphan*/  njs_uint_t ;

/* Variables and functions */
 void* njs_mp_align (void*,size_t,size_t) ; 

__attribute__((used)) static void *
lvlhsh_pool_alloc(void *pool, size_t size, njs_uint_t nalloc)
{
    return njs_mp_align(pool, size, size);
}