#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  global; } ;
typedef  int /*<<< orphan*/  OSSL_EX_DATA_GLOBAL ;
typedef  TYPE_1__ OPENSSL_CTX ;

/* Variables and functions */
 TYPE_1__* openssl_ctx_get_concrete (TYPE_1__*) ; 

OSSL_EX_DATA_GLOBAL *openssl_ctx_get_ex_data_global(OPENSSL_CTX *ctx)
{
    ctx = openssl_ctx_get_concrete(ctx);
    if (ctx == NULL)
        return NULL;
    return &ctx->global;
}