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
struct TYPE_3__ {size_t max_len; size_t len; unsigned char* buffer; } ;
typedef  TYPE_1__ RAND_POOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  RAND_F_RAND_POOL_ADD_BEGIN ; 
 int /*<<< orphan*/  RAND_R_RANDOM_POOL_OVERFLOW ; 
 int /*<<< orphan*/  RANDerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned char *rand_pool_add_begin(RAND_POOL *pool, size_t len)
{
    if (len == 0)
        return NULL;

    if (len > pool->max_len - pool->len) {
        RANDerr(RAND_F_RAND_POOL_ADD_BEGIN, RAND_R_RANDOM_POOL_OVERFLOW);
        return NULL;
    }

    if (pool->buffer == NULL) {
        RANDerr(RAND_F_RAND_POOL_ADD_BEGIN, ERR_R_INTERNAL_ERROR);
        return NULL;
    }

    return pool->buffer + pool->len;
}