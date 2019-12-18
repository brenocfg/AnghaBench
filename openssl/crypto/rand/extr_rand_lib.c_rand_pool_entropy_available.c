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
struct TYPE_3__ {scalar_t__ entropy; scalar_t__ entropy_requested; scalar_t__ len; scalar_t__ min_len; } ;
typedef  TYPE_1__ RAND_POOL ;

/* Variables and functions */

size_t rand_pool_entropy_available(RAND_POOL *pool)
{
    if (pool->entropy < pool->entropy_requested)
        return 0;

    if (pool->len < pool->min_len)
        return 0;

    return pool->entropy;
}