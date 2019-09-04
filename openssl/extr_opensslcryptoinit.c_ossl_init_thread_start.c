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
typedef  int uint64_t ;
struct thread_local_inits_st {int async; int err_state; int rand; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT ; 
 int OPENSSL_INIT_THREAD_ASYNC ; 
 int OPENSSL_INIT_THREAD_ERR_STATE ; 
 int OPENSSL_INIT_THREAD_RAND ; 
 int /*<<< orphan*/  OPENSSL_init_crypto (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_TRACE (int /*<<< orphan*/ ,char*) ; 
 struct thread_local_inits_st* ossl_init_get_thread_local (int) ; 

int ossl_init_thread_start(uint64_t opts)
{
    struct thread_local_inits_st *locals;

    if (!OPENSSL_init_crypto(0, NULL))
        return 0;

    locals = ossl_init_get_thread_local(1);

    if (locals == NULL)
        return 0;

    if (opts & OPENSSL_INIT_THREAD_ASYNC) {
        OSSL_TRACE(INIT,
                   "ossl_init_thread_start: "
                   "marking thread for async\n");
        locals->async = 1;
    }

    if (opts & OPENSSL_INIT_THREAD_ERR_STATE) {
        OSSL_TRACE(INIT,
                   "ossl_init_thread_start: "
                   "marking thread for err_state\n");
        locals->err_state = 1;
    }

    if (opts & OPENSSL_INIT_THREAD_RAND) {
        OSSL_TRACE(INIT,
                   "ossl_init_thread_start: "
                   "marking thread for rand\n");
        locals->rand = 1;
    }

    return 1;
}