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
struct TYPE_5__ {int /*<<< orphan*/  provctx; TYPE_1__* cipher; } ;
struct TYPE_4__ {int (* set_ctx_params ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ;} ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  TYPE_2__ EVP_CIPHER_CTX ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

int EVP_CIPHER_CTX_set_params(EVP_CIPHER_CTX *ctx, const OSSL_PARAM params[])
{
    if (ctx->cipher != NULL && ctx->cipher->set_ctx_params != NULL)
        return ctx->cipher->set_ctx_params(ctx->provctx, params);
    return 0;
}