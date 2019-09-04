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
struct TYPE_3__ {int /*<<< orphan*/  (* cleanup ) () ;} ;
typedef  TYPE_1__ RAND_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAND_set_rand_method (int /*<<< orphan*/ *) ; 
 TYPE_1__* default_RAND_meth ; 
 int /*<<< orphan*/ * rand_engine_lock ; 
 scalar_t__ rand_inited ; 
 int /*<<< orphan*/ * rand_meth_lock ; 
 int /*<<< orphan*/ * rand_nonce_lock ; 
 int /*<<< orphan*/  rand_pool_cleanup () ; 
 int /*<<< orphan*/  stub1 () ; 

void rand_cleanup_int(void)
{
    const RAND_METHOD *meth = default_RAND_meth;

    if (!rand_inited)
        return;

    if (meth != NULL && meth->cleanup != NULL)
        meth->cleanup();
    RAND_set_rand_method(NULL);
    rand_pool_cleanup();
#ifndef OPENSSL_NO_ENGINE
    CRYPTO_THREAD_lock_free(rand_engine_lock);
    rand_engine_lock = NULL;
#endif
    CRYPTO_THREAD_lock_free(rand_meth_lock);
    rand_meth_lock = NULL;
    CRYPTO_THREAD_lock_free(rand_nonce_lock);
    rand_nonce_lock = NULL;
    rand_inited = 0;
}