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
struct TYPE_3__ {int /*<<< orphan*/ * lock; } ;
typedef  TYPE_1__ RAND_DRBG ;

/* Variables and functions */
 int CRYPTO_THREAD_unlock (int /*<<< orphan*/ *) ; 

int rand_drbg_unlock(RAND_DRBG *drbg)
{
    if (drbg->lock != NULL)
        return CRYPTO_THREAD_unlock(drbg->lock);

    return 1;
}