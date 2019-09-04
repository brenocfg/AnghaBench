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
struct mp_image_pool {void* allocator_ctx; int /*<<< orphan*/  allocator; } ;
typedef  int /*<<< orphan*/  mp_image_allocator ;

/* Variables and functions */

void mp_image_pool_set_allocator(struct mp_image_pool *pool,
                                 mp_image_allocator cb, void  *cb_data)
{
    pool->allocator = cb;
    pool->allocator_ctx = cb_data;
}