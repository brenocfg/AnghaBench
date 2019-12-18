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
typedef  int /*<<< orphan*/  async_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_set_local (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * async_get_ctx () ; 
 int /*<<< orphan*/  ctxkey ; 

__attribute__((used)) static int async_ctx_free(void)
{
    async_ctx *ctx;

    ctx = async_get_ctx();

    if (!CRYPTO_THREAD_set_local(&ctxkey, NULL))
        return 0;

    OPENSSL_free(ctx);

    return 1;
}