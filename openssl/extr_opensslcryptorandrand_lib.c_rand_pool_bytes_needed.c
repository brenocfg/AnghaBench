#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t max_len; size_t len; scalar_t__ min_len; } ;
typedef  TYPE_1__ RAND_POOL ;

/* Variables and functions */
 size_t ENTROPY_TO_BYTES (size_t,unsigned int) ; 
 int /*<<< orphan*/  RAND_F_RAND_POOL_BYTES_NEEDED ; 
 int /*<<< orphan*/  RAND_R_ARGUMENT_OUT_OF_RANGE ; 
 int /*<<< orphan*/  RAND_R_RANDOM_POOL_OVERFLOW ; 
 int /*<<< orphan*/  RANDerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t rand_pool_entropy_needed (TYPE_1__*) ; 

size_t rand_pool_bytes_needed(RAND_POOL *pool, unsigned int entropy_factor)
{
    size_t bytes_needed;
    size_t entropy_needed = rand_pool_entropy_needed(pool);

    if (entropy_factor < 1) {
        RANDerr(RAND_F_RAND_POOL_BYTES_NEEDED, RAND_R_ARGUMENT_OUT_OF_RANGE);
        return 0;
    }

    bytes_needed = ENTROPY_TO_BYTES(entropy_needed, entropy_factor);

    if (bytes_needed > pool->max_len - pool->len) {
        /* not enough space left */
        RANDerr(RAND_F_RAND_POOL_BYTES_NEEDED, RAND_R_RANDOM_POOL_OVERFLOW);
        return 0;
    }

    if (pool->len < pool->min_len &&
        bytes_needed < pool->min_len - pool->len)
        /* to meet the min_len requirement */
        bytes_needed = pool->min_len - pool->len;

    return bytes_needed;
}