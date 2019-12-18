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
struct TYPE_3__ {scalar_t__ blocked; int /*<<< orphan*/ * currjob; } ;
typedef  TYPE_1__ async_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_INIT_ASYNC ; 
 int /*<<< orphan*/  OPENSSL_init_crypto (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* async_get_ctx () ; 

void ASYNC_unblock_pause(void)
{
    async_ctx *ctx;

    if (!OPENSSL_init_crypto(OPENSSL_INIT_ASYNC, NULL))
        return;

    ctx = async_get_ctx();
    if (ctx == NULL || ctx->currjob == NULL) {
        /*
         * We're not in a job anyway so ignore this
         */
        return;
    }
    if (ctx->blocked > 0)
        ctx->blocked--;
}