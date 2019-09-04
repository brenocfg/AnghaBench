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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct ra_buf_pool {int /*<<< orphan*/  num_buffers; TYPE_1__ current_params; int /*<<< orphan*/  index; int /*<<< orphan*/  buffers; } ;
struct ra_buf {int dummy; } ;
struct ra {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_INSERT_AT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ra_buf*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ra*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ra_buf* ra_buf_create (struct ra*,TYPE_1__*) ; 

__attribute__((used)) static bool ra_buf_pool_grow(struct ra *ra, struct ra_buf_pool *pool)
{
    struct ra_buf *buf = ra_buf_create(ra, &pool->current_params);
    if (!buf)
        return false;

    MP_TARRAY_INSERT_AT(NULL, pool->buffers, pool->num_buffers, pool->index, buf);
    MP_VERBOSE(ra, "Resized buffer pool of type %u to size %d\n",
               pool->current_params.type, pool->num_buffers);
    return true;
}