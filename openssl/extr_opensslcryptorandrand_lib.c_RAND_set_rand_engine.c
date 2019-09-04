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
 int /*<<< orphan*/  ENGINE_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAND_set_rand_method (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_rand_init ; 
 int /*<<< orphan*/ * funct_ref ; 
 int /*<<< orphan*/  rand_engine_lock ; 
 int /*<<< orphan*/  rand_init ; 

int RAND_set_rand_engine(ENGINE *engine)
{
    const RAND_METHOD *tmp_meth = NULL;

    if (!RUN_ONCE(&rand_init, do_rand_init))
        return 0;

    if (engine != NULL) {
        if (!ENGINE_init(engine))
            return 0;
        tmp_meth = ENGINE_get_RAND(engine);
        if (tmp_meth == NULL) {
            ENGINE_finish(engine);
            return 0;
        }
    }
    CRYPTO_THREAD_write_lock(rand_engine_lock);
    /* This function releases any prior ENGINE so call it first */
    RAND_set_rand_method(tmp_meth);
    funct_ref = engine;
    CRYPTO_THREAD_unlock(rand_engine_lock);
    return 1;
}