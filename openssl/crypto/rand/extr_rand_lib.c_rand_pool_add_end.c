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
struct TYPE_3__ {size_t alloc_len; size_t len; size_t entropy; } ;
typedef  TYPE_1__ RAND_POOL ;

/* Variables and functions */
 int /*<<< orphan*/  RAND_F_RAND_POOL_ADD_END ; 
 int /*<<< orphan*/  RAND_R_RANDOM_POOL_OVERFLOW ; 
 int /*<<< orphan*/  RANDerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rand_pool_add_end(RAND_POOL *pool, size_t len, size_t entropy)
{
    if (len > pool->alloc_len - pool->len) {
        RANDerr(RAND_F_RAND_POOL_ADD_END, RAND_R_RANDOM_POOL_OVERFLOW);
        return 0;
    }

    if (len > 0) {
        pool->len += len;
        pool->entropy += entropy;
    }

    return 1;
}