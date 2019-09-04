#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  global; } ;
typedef  int /*<<< orphan*/  OSSL_EX_DATA_GLOBAL ;
typedef  TYPE_1__ OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* default_context ; 
 int /*<<< orphan*/  default_context_init ; 
 int /*<<< orphan*/  do_default_context_init ; 

OSSL_EX_DATA_GLOBAL *openssl_ctx_get_ex_data_global(OPENSSL_CTX *ctx)
{
    /*
     * The default context code is not needed in FIPS_MODE and ctx should never
     * be NULL in the FIPS provider. However we compile this code out to ensure
     * we fail immediately if ctx == NULL in FIPS_MODE
     */
#ifndef FIPS_MODE
    if (ctx == NULL) {
        if (!RUN_ONCE(&default_context_init, do_default_context_init))
            return NULL;
        ctx = default_context;
    }
#endif
    if (ctx == NULL)
        return NULL;
    return &ctx->global;
}