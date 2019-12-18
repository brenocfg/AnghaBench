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
struct TYPE_3__ {unsigned char* oiv; int /*<<< orphan*/  provctx; int /*<<< orphan*/  cipher; } ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  TYPE_1__ EVP_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_IV ; 
 int /*<<< orphan*/  OSSL_PARAM_END ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_octet_ptr (int /*<<< orphan*/ ,void**,int) ; 
 int evp_do_ciph_ctx_getparams (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

const unsigned char *EVP_CIPHER_CTX_original_iv(const EVP_CIPHER_CTX *ctx)
{
    int ok;
    const unsigned char *v = ctx->oiv;
    OSSL_PARAM params[2] = { OSSL_PARAM_END, OSSL_PARAM_END };

    params[0] =
        OSSL_PARAM_construct_octet_ptr(OSSL_CIPHER_PARAM_IV,
                                       (void **)&v, sizeof(ctx->oiv));
    ok = evp_do_ciph_ctx_getparams(ctx->cipher, ctx->provctx, params);

    return ok != 0 ? v : NULL;
}