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
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/ * openssl_ctx_get_concrete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_ctx_thread_stop (int /*<<< orphan*/ *) ; 

void OPENSSL_thread_stop_ex(OPENSSL_CTX *ctx)
{
    ctx = openssl_ctx_get_concrete(ctx);
    /*
     * TODO(3.0). It would be nice if we could figure out a way to do this on
     * all threads that have used the OPENSSL_CTX when the OPENSSL_CTX is freed.
     * This is currently not possible due to the use of thread local variables.
     */
    ossl_ctx_thread_stop(ctx);
}