#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* meth; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {scalar_t__ (* get_params ) (int /*<<< orphan*/ *) ;scalar_t__ (* get_ctx_params ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  TYPE_2__ EVP_KDF_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OSSL_KDF_PARAM_SIZE ; 
 int /*<<< orphan*/  OSSL_PARAM_END ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_size_t (int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *) ; 

size_t EVP_KDF_size(EVP_KDF_CTX *ctx)
{
    OSSL_PARAM params[2] = { OSSL_PARAM_END, OSSL_PARAM_END };
    size_t s;

    if (ctx == NULL)
        return 0;

    *params = OSSL_PARAM_construct_size_t(OSSL_KDF_PARAM_SIZE, &s);
    if (ctx->meth->get_ctx_params != NULL
        && ctx->meth->get_ctx_params(ctx->data, params))
            return s;
    if (ctx->meth->get_params != NULL
        && ctx->meth->get_params(params))
            return s;
    return 0;
}