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
struct ra_buf_params {int /*<<< orphan*/  initial_data; } ;
struct ra_buf_pool {size_t index; size_t num_buffers; struct ra_buf** buffers; struct ra_buf_params current_params; } ;
struct ra_buf {int dummy; } ;
struct ra {TYPE_1__* fns; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* buf_poll ) (struct ra*,struct ra_buf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ra_buf_params_compatible (struct ra_buf_params const*,struct ra_buf_params*) ; 
 int /*<<< orphan*/  ra_buf_pool_grow (struct ra*,struct ra_buf_pool*) ; 
 int /*<<< orphan*/  ra_buf_pool_uninit (struct ra*,struct ra_buf_pool*) ; 
 int /*<<< orphan*/  stub1 (struct ra*,struct ra_buf*) ; 

struct ra_buf *ra_buf_pool_get(struct ra *ra, struct ra_buf_pool *pool,
                               const struct ra_buf_params *params)
{
    assert(!params->initial_data);

    if (!ra_buf_params_compatible(params, &pool->current_params)) {
        ra_buf_pool_uninit(ra, pool);
        pool->current_params = *params;
    }

    // Make sure we have at least one buffer available
    if (!pool->buffers && !ra_buf_pool_grow(ra, pool))
        return NULL;

    // Make sure the next buffer is available for use
    if (!ra->fns->buf_poll(ra, pool->buffers[pool->index]) &&
        !ra_buf_pool_grow(ra, pool))
    {
        return NULL;
    }

    struct ra_buf *buf = pool->buffers[pool->index++];
    pool->index %= pool->num_buffers;

    return buf;
}