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
struct mp_aframe_pool {int /*<<< orphan*/  avpool; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_pool_uninit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mp_aframe_pool_destructor(void *p)
{
    struct mp_aframe_pool *pool = p;
    av_buffer_pool_uninit(&pool->avpool);
}