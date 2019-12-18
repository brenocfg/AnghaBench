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
typedef  int /*<<< orphan*/  RAND_POOL ;

/* Variables and functions */
 scalar_t__ rand_pool_add_additional_data (int /*<<< orphan*/ *) ; 
 unsigned char* rand_pool_detach (int /*<<< orphan*/ *) ; 
 size_t rand_pool_length (int /*<<< orphan*/ *) ; 

size_t rand_drbg_get_additional_data(RAND_POOL *pool, unsigned char **pout)
{
    size_t ret = 0;

    if (rand_pool_add_additional_data(pool) == 0)
        goto err;

    ret = rand_pool_length(pool);
    *pout = rand_pool_detach(pool);

 err:
    return ret;
}