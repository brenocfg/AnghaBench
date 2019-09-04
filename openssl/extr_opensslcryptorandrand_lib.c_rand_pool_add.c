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
struct TYPE_3__ {size_t max_len; size_t len; size_t entropy; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ RAND_POOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  RAND_F_RAND_POOL_ADD ; 
 int /*<<< orphan*/  RAND_R_ENTROPY_INPUT_TOO_LONG ; 
 int /*<<< orphan*/  RANDerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

int rand_pool_add(RAND_POOL *pool,
                  const unsigned char *buffer, size_t len, size_t entropy)
{
    if (len > pool->max_len - pool->len) {
        RANDerr(RAND_F_RAND_POOL_ADD, RAND_R_ENTROPY_INPUT_TOO_LONG);
        return 0;
    }

    if (pool->buffer == NULL) {
        RANDerr(RAND_F_RAND_POOL_ADD, ERR_R_INTERNAL_ERROR);
        return 0;
    }

    if (len > 0) {
        memcpy(pool->buffer + pool->len, buffer, len);
        pool->len += len;
        pool->entropy += entropy;
    }

    return 1;
}