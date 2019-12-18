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
struct TYPE_4__ {int /*<<< orphan*/  cipher; int /*<<< orphan*/  provctx; } ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  TYPE_1__ EVP_CIPHER_CTX ;

/* Variables and functions */
 int EVP_CIPHER_CTX_ctrl (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int EVP_CIPHER_flags (int /*<<< orphan*/ ) ; 
 int EVP_CIPHER_iv_length (int /*<<< orphan*/ ) ; 
 int EVP_CIPH_CUSTOM_IV_LENGTH ; 
 int /*<<< orphan*/  EVP_CTRL_GET_IVLEN ; 
 int EVP_CTRL_RET_UNSUPPORTED ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_IVLEN ; 
 int /*<<< orphan*/  OSSL_PARAM_END ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_size_t (int /*<<< orphan*/ ,size_t*) ; 
 int evp_do_ciph_ctx_getparams (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int EVP_CIPHER_CTX_iv_length(const EVP_CIPHER_CTX *ctx)
{
    int rv, len = EVP_CIPHER_iv_length(ctx->cipher);
    size_t v = len;
    OSSL_PARAM params[2] = { OSSL_PARAM_END, OSSL_PARAM_END };

    params[0] = OSSL_PARAM_construct_size_t(OSSL_CIPHER_PARAM_IVLEN, &v);
    rv = evp_do_ciph_ctx_getparams(ctx->cipher, ctx->provctx, params);
    if (rv == EVP_CTRL_RET_UNSUPPORTED)
        goto legacy;
    return rv != 0 ? (int)v : -1;
    /* TODO (3.0) Remove legacy support */
legacy:
    if ((EVP_CIPHER_flags(ctx->cipher) & EVP_CIPH_CUSTOM_IV_LENGTH) != 0) {
        rv = EVP_CIPHER_CTX_ctrl((EVP_CIPHER_CTX *)ctx, EVP_CTRL_GET_IVLEN,
                                 0, &len);
        return (rv == 1) ? len : -1;
    }
    return len;
}