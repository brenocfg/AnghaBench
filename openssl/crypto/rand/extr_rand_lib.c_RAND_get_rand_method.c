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
typedef  int /*<<< orphan*/  RAND_METHOD ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ENGINE_get_RAND (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ENGINE_get_default_RAND () ; 
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* default_RAND_meth ; 
 int /*<<< orphan*/  do_rand_init ; 
 int /*<<< orphan*/ * funct_ref ; 
 int /*<<< orphan*/  rand_init ; 
 int /*<<< orphan*/  rand_meth ; 
 int /*<<< orphan*/  rand_meth_lock ; 

const RAND_METHOD *RAND_get_rand_method(void)
{
#ifdef FIPS_MODE
    return NULL;
#else
    const RAND_METHOD *tmp_meth = NULL;

    if (!RUN_ONCE(&rand_init, do_rand_init))
        return NULL;

    CRYPTO_THREAD_write_lock(rand_meth_lock);
    if (default_RAND_meth == NULL) {
# ifndef OPENSSL_NO_ENGINE
        ENGINE *e;

        /* If we have an engine that can do RAND, use it. */
        if ((e = ENGINE_get_default_RAND()) != NULL
                && (tmp_meth = ENGINE_get_RAND(e)) != NULL) {
            funct_ref = e;
            default_RAND_meth = tmp_meth;
        } else {
            ENGINE_finish(e);
            default_RAND_meth = &rand_meth;
        }
# else
        default_RAND_meth = &rand_meth;
# endif
    }
    tmp_meth = default_RAND_meth;
    CRYPTO_THREAD_unlock(rand_meth_lock);
    return tmp_meth;
#endif
}